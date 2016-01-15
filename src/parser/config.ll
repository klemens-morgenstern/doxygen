/******************************************************************************
 *
 * Copyright (C) 1997-2015 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 */
%option never-interactive
%{

/*
 *	includes
 */

#include <config_parser.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <config.hpp>
#include <stack>
#include <boost/algorithm/string/trim.hpp>
#include <boost/type_index.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using namespace DoxyFrame::Config;

#define YY_NO_INPUT 1
#define YY_NO_UNISTD_H 1

#define MAX_INCLUDE_DEPTH 10
#define YY_NEVER_INTERACTIVE 1



/* -----------------------------------------------------------------
 *
 *	static variables. Are declared thread_local so parallel parsing maybe possible. , but still.
 */

static RawOption * current_option = nullptr;
static RawOption &o() {return *current_option;}

struct file_reader
{
	int 	line_nr = 0;
	string file_name;
	string input_buffer;
	string::const_iterator input_buffer_iterator = input_buffer.begin();
	file_reader(const std::string & file_name, std::string &&data) : file_name(file_name), input_buffer(std::move(data))
	{
	}
};

static stack<file_reader, vector<file_reader>> include_stack;

///shortcut
static file_reader &f() {return include_stack.top();};


static string 			 user_comment;
static int               lastState;

static string 	   		 start_comment;

static RawOption	 	 include_path;
static std::string 		 encoding = "UTF-8";

static string		 qStringBuf;
static string		 GetStrList_buf;


/* -----------------------------------------------------------------
 */
#undef	YY_INPUT
#define	YY_INPUT(buf,result,max_size) result=yyread(buf,result, max_size);
static int yyread(char *buf, int &bytes_read, int max_size)
{
	auto &itr = f().input_buffer_iterator;
	int bytes_available = f().input_buffer.end() - itr;
						
	int bytes_to_read = (bytes_available > max_size) ? max_size : bytes_available ;
	
	copy(itr, itr + bytes_to_read, buf);
	itr += bytes_to_read;
	
	bytes_read = bytes_to_read;

	return bytes_read;
}

//Overwrite YY_DECL

#define YY_DECL float lexscan( RawConfig &raw_cfg )

namespace DoxyFrame
{
namespace Config
{
static bool parse_include_file(RawConfig &rc, const std::string & file_name, const std::string & encoding);
}}

%}

%option noyywrap

%x      PreStart
%x      Start
%x		SkipComment
%x      GetStrList
%x      GetQuotedString
%x      GetEnvVar
%x      Include

%%

<*>\0x0d
<PreStart>"##".*"\n" { raw_cfg.startComment += yytext; }
<PreStart>. {
              BEGIN(Start);
              unput(*yytext);
            }
<Start,GetStrList>"##".*"\n" { user_comment += yytext; }
<Start,GetStrList>"#"	   	 { BEGIN(SkipComment); }
<Start>[a-z_A-Z\.][a-z_A-Z0-9\.]*[ \t]*"=" {
								string opt_name = yytext;
								/* ok, get the Option here */
								opt_name.resize(opt_name.size()-1); //remove the "="
								boost::trim(opt_name);
								current_option = &raw_cfg[opt_name];
								std::swap(current_option->comment, user_comment); //put the comment in the thingy.
								user_comment.clear();
								current_option->data.clear();
								BEGIN(GetStrList);
							}
<Start>[a-z_A-Z\.][a-z_A-Z0-9\.]*[ \t]*"+="	{
					 			string opt_name = yytext;
					 			/* ok, get the Option here */
					 			opt_name.resize(opt_name.size()-2) ; //remove the `#='
					 			boost::trim(opt_name);

					 			current_option->comment += user_comment;
					 			user_comment = "";
								BEGIN(GetStrList);
							}
<Start>"@INCLUDE_PATH"[ \t]*"=" { BEGIN(GetStrList); current_option = &include_path; }
<Start>"@INCLUDE"[ \t]*"=" { BEGIN(Include); }
<Include>([^ \"\t\r\n]+)|("\""[^\n\"]+"\"") { 
						parse_include_file(raw_cfg, yytext, "UTF-8") ;
  					  	BEGIN(Start);
					}
<<EOF>>				{
					  	include_stack.pop();
                        if (include_stack.empty())
					  	{
					    	yyterminate();
					  	}
					}

<Start>[a-z_A-Z0-9]+ { cerr << "ignoring unknown tag `" << yytext << "' at line " << f().line_nr << ", file " << f().file_name << endl; }
<GetStrList>\n			{ 
  					  		f().line_nr++; 
					  		if (!GetStrList_buf.empty()) //TODO:
					  		{
					    		//printf("elemStr1=`%s'\n",elemStr.data());
					    		o().data.push_back(std::move(GetStrList_buf));
					    		GetStrList_buf.clear();
					  		}
					  		BEGIN(Start); 
						}
<GetStrList>[ \t]+		{
							if (!GetStrList_buf.empty()) //TODO:
							{
								//printf("elemStr1=`%s'\n",elemStr.data());
								o().data.push_back(std::move(GetStrList_buf));
								GetStrList_buf.clear();
							}
  						}
<GetStrList>"\""	{
						lastState=YY_START;
						BEGIN(GetQuotedString);
						qStringBuf.clear();
						//tmpString.resize(0);
					}
<GetQuotedString>"\""|"\n" 		{ 
                                	// we add a bogus space to signal that the string was quoted. This space will be stripped later on.
				  					GetStrList_buf += qStringBuf ;
					  				if (*yytext=='\n')
					  				{
					  					cerr << "Missing end quote (\") on line " << f().line_nr 
					  						 << ", file " << f().file_name << endl;
					   					f().line_nr++;
					  				}
					  				BEGIN(lastState);
  								}
<GetQuotedString>"\\\""		{
  					 			 qStringBuf+='"';
  							}
<GetQuotedString>.			{ qStringBuf += *yytext; }

<GetStrList>[^ \#\"\t\r\n]+		{ GetStrList_buf += yytext; }
  					
<SkipComment>\n				{ f().line_nr++; BEGIN(Start); }
<SkipComment>\\[ \r\t]*\n	{ f().line_nr++; BEGIN(Start); }
<*>\\[ \r\t]*\n				{ f().line_nr++; }
<*>.					
<*>\n						{ f().line_nr++ ; }

%%

/*@ ----------------------------------------------------------------------------
 */

namespace DoxyFrame
{
namespace Config
{

bool parse_string(RawConfig &rc, const string &filename , string &&content)
{

	include_stack.emplace(file_reader(filename, std::move(content)));

  	BEGIN( PreStart );


  	return lexscan (rc);;
}
bool parse_include_file(RawConfig &rc, const std::string & file_name, const std::string & encoding)
{
	ifstream fs(file_name);

	stringstream ss;
	ss << fs.rdbuf();

	return parse_string(rc, file_name, ss.str());

}

bool parse_file(RawConfig &rc, const string& filename)
{
	ifstream fs(filename);

	stringstream ss;
	ss << fs.rdbuf();

  	int retval;

  	//printlex(yy_flex_debug, true, __FILE__, filename);
  	retval =  parse_string(rc, filename, ss.str());
  	//printlex(yy_flex_debug, false, __FILE__, filename);
 	return retval;
}
}}
int main()
{
	RawConfig rc;

	parse_file(rc, "spec.doxyfile");
	std::cerr << "Ran through" << std::endl;

	for (auto &x : rc)
	{
		cout << x.first <<": {";
		for (auto & s : x.second.data)
			cout << s << ", ";
		cout << "}" <<endl;
	}

	return 1;
}
