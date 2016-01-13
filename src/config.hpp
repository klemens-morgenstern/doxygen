/******************************************************************************
 *
 * 
 *
 *
 * Copyright (C) 1997-2015 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <regex>
#include <ostream>
#include <istream>
#include <boost/range/iterator_range.hpp>
#include <boost/variant.hpp>
#include <boost/type_index.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/none.hpp>

namespace DoxyFrame
{

namespace Config
{


template<typename T>
struct OptionTpl
{
	T value;
	boost::optional<T> default_value;
};

struct StringList : OptionTpl<std::vector<std::string>>
{};

struct PathList	: OptionTpl<std::vector<boost::filesystem::path>>
{};

struct String 	: OptionTpl<std::string>
{};

struct Path 	: OptionTpl<boost::filesystem::path>
{};


struct Enum 	: OptionTpl<std::string>
{
	std::unordered_set<std::string> allowed_values;
};

struct Bool : OptionTpl<bool>
{};

struct Int  : OptionTpl<int>
{
	int min;
	int max;
};

struct Info		{};
struct Obsolete {};
struct Disabled {};
struct Unknown	{std::string value;};


struct Option
{
	std::string name;
	std::string doc;
	std::string dependency;
	std::string encoding;
	std::string user_comment;

	std::string description;
	bool set = false;

	using Entry = boost::variant<boost::none_t,
			StringList, PathList,
			String, Path, Enum,
			Bool, Int, Info>;

	Entry entry;

};

bool operator==(const Option& lhs, const Option &rhs) {return lhs.name == rhs.name;};
bool operator!=(const Option& lhs, const Option &rhs) {return lhs.name != rhs.name;};

// some convenience macros for access the config options
#define DOXY_CONFIG_GET_STRING(val)  	 ::DoxyFrame::Config::getString		(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_PATH(val)  		 ::DoxyFrame::Config::getPath		(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_INT(val)     	 ::DoxyFrame::Config::getInt		(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_STRING_LIST(val) ::DoxyFrame::Config::getStringList	(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_PATH_LIST(val)   ::DoxyFrame::Config::getPathList	(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_ENUM(val)    	 ::DoxyFrame::Config::getEnum		(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET_BOOL(val)    	 ::DoxyFrame::Config::getBool		(val, __FILE__, __LINE__);
#define DOXY_CONFIG_GET(val)			 ::DoxyFrame::Config::get			(val, __FILE__, __LINE__);

/** Singleton for configuration variables.
 *
 *  This object holds the global static variables
 *  read from a user-supplied configuration file.
 *  The static member instance() can be used to get
 *  a pointer to the one and only instance.
 *  
 *  Set all variables to their default values by
 *  calling Config::instance()->init()
 *
 */
class Config
{
  public:
    /////////////////////////////
    // public API
    /////////////////////////////

    /*! Returns the one and only instance of this class */
    static Config &instance()
    {
      if (m_instance == nullptr) m_instance = std::make_unique<Config>();
      return *m_instance;
    }
    /*! Delete the instance */
    static void deleteInstance()
    {
      m_instance = nullptr;
    }
    
    /*! Returns an range that can by used to iterate over the
     *  configuration options.
     */
    boost::iterator_range<typename std::vector<Option>::iterator> options()
    {
      return boost::make_iterator_range(m_options);
    }

    /*! Writes a template configuration to stream \a t. If \a shortIndex
     *  is \c TRUE the description of each configuration option will
     *  be omitted.
     */
    void writeTemplate(std::ostream &t,bool shortIndex,bool updateOnly);

    void setHeader(const std::string &header) { m_header = header; }

    /////////////////////////////
    // internal API
    /////////////////////////////

    /*! Converts the string values read from the configuration file
     *  to real values for non-string type options (like int, and bools)
     */
    void convertStrToVal();

    /*! Replaces references to environment variable by the actual value
     *  of the environment variable.
     */
    void substituteEnvironmentVars();

    /*! Checks if the values of the variable are correct, adjusts them
     *  if needed, and report any errors.
     */
    void check();

    /*! Initialize config variables to their default value */
    void init();

    /*! Parse a configuration data in string \a str.
     *  \returns TRUE if successful, or FALSE if the string could not be
     *  parsed.
     */ 
    //bool parseString(const std::string &fn,const std::string &str);
    bool parseString(const std::string &fn,const std::string &str,bool upd = FALSE);

    /*! Parse a configuration file with name \a fn.
     *  \returns TRUE if successful, FALSE if the file could not be 
     *  opened or read.
     */ 
    bool parse(const std::string &fn,bool upd = FALSE);


    /*! Append user start comment
     */
    void appendStartComment(const QCString &u)
    {
      m_startComment += u;
    }
    /*! Append user comment
     */
    void appendUserComment(const QCString &u)
    {
      m_userComment += u;
    }
    /*! Take the user start comment and reset it internally
     *  \returns user start comment
     */
    QCString takeStartComment()
    {
      QCString result=m_startComment;
      m_startComment.resize(0);
      return result.replace(QRegExp("\r"),"");
    }
    /*! Take the user comment and reset it internally
     *  \returns user comment
     */
    QCString takeUserComment()
    {
      QCString result=m_userComment;
      m_userComment.resize(0);
      return result.replace(QRegExp("\r"),"");
    }

    static std::string configStringRecode(
        const std::string &str,
        const std::string &fromEncoding,
        const std::string &toEncoding);

    Info   		&addInfo	(const std::string &name, const std::string &doc);
    String 		&addString	(const std::string &name, const std::string &doc);
    Enum 		&addEnum	(const std::string &name, const std::string &doc, const std::string &defVal);
    StringList  &addStringList(const std::string &name, const std::string &doc);
    StringList  &addPathList(const std::string &name, const std::string &doc);
    Int    		&addInt		(const std::string &name, const std::string &doc, int minVal,int maxVal,int defVal);
    Bool   		&addBool	(const std::string &name, const std::string &doc,bool defVal);
    Option 		&addObsolete(const std::string &name);
    Option 		&addDisabled(const std::string &name);


    Config() {}
   ~Config() {}


  protected:


   static std::string convertToComment(const std::string &s, const std::string &u);
   static void Config::addConfigOptions(Config &cfg);
  private:
    void checkFileName(const std::string &);
    std::vector<Option> m_options;
    std::vector<Option> m_obsolete;
    std::vector<Option> m_disabled;
    std::vector<Option> m_unknown;
    static std::unique_ptr<Config> m_instance;

    std::string m_startComment;
    std::string m_userComment;
    std::string m_header;
};

std::string 				&getString(const std::string &name, const std::string &fileName = "", int num = -1);
boost::filesystem::path 	&getPath  (const std::string &name, const std::string &fileName = "", int num = -1);
std::vector<std::string>	&getStringList(const std::string &name, const std::string &fileName = "", int num = -1);
std::vector<boost::filesystem::path> &getPathList(const std::string &name, const std::string &fileName = "", int num = -1);
std::string  			&getEnum  (const std::string &name, const std::string &fileName = "", int num = -1);
int      				&getInt   (const std::string &name, const std::string &fileName = "", int num = -1);
bool     				&getBool  (const std::string &name, const std::string &fileName = "", int num = -1);
Option 	 				&get	  (const std::string &name, const std::string &fileName = "", int num = -1);

inline Info   		&addInfo  	(const std::string &name, const std::string &doc) 	{return Config::instance().addInfo(name, doc);}
inline String 	 	&addString	(const std::string &name, const std::string &doc)	{return Config::instance().addString(name, doc);}
inline Enum 		&addEnum	(const std::string &name, const std::string &doc, const std::string &defVal) {return Config::instance().addEnum(name, doc, defVal); }
inline StringList  	&addStringList(const std::string &name, const std::string &doc)	{return Config::instance().addStringList(name, doc);}
inline StringList  	&addPathList(const std::string &name, const std::string &doc)	{return Config::instance().addPathList(name, doc);}
inline Int    		&addInt		(const std::string &name, const std::string &doc, int minVal,int maxVal,int defVal) {return Config::instance().addInt(name, doc, minVal, maxVal, defVal);}
inline Bool   	 	&addBool	(const std::string &name, const std::string &doc,bool defVal) {return Config::instance().addBool(name, doc, defVal);}
inline Option 	 	&addObsolete(const std::string &name) {return Config::instance().addObsolete(name);}
inline Option 	 	&addDisabled(const std::string &name) {return Config::instance().addDisabled(name);}


}
}




#endif
