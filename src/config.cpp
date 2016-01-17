/**
 * @file   config.cpp
 * @date   12.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */


#include <doxyframe/config.hpp>
#include <doxyframe/error_log.hpp>
#include <version.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/type_index.hpp>
#include <boost/locale.hpp>

using namespace DoxyFrame::Log;

using boost::locale::conv::from_utf;
using boost::locale::conv::to_utf;

namespace DoxyFrame
{

namespace Config
{

std::unique_ptr<Config> Config::m_instance;

/*!
*  @name Getting configuration values.
*  @{
*/
//TODO: CHECK if these functions can return a const reference.
/*! Returns the value of the string option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getString() for this.
*/
std::string &Config::getString(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<String>())
	{
		Log::Error(fileName, num) << "Requested option " << name << " not a string!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<String>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << "\t" <<val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}

/*! Returns the value of the string option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getString() for this.
*/
boost::filesystem::path &Config::getPath(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<Path>())
	{
		Log::Error(fileName, num) << "nternal error: Requested option " << name << " not a path!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Path>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Internal error: Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}

/*! Returns the value of the list option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getList() for this.
*/
std::vector<std::string> &Config::getStringList(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<StringList>())
	{
		Log::Error(fileName, num) << "Requested option " << name << " not a string list!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<StringList>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}

/*! Returns the value of the list option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getList() for this.
*/
std::vector<boost::filesystem::path> &Config::getPathList(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<PathList>())
	{
		Log::Error(fileName, num) << "Requested option " << name << " not a path list!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<PathList>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}

/*! Returns the value of the enum option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getEnum() for this.
*/
std::string  &Config::getEnum(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<Enum>())
	{
		Log::Error(fileName, num) << "Requested option " << name << " not an enumerator!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Enum>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}

/*! Returns the value of the integer option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getInt() for this.
*/
int &Config::getInt(const std::string &name, const std::string &fileName ,int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<Int>())
	{
		Log::Error(fileName, num) << "Requested option " << name << " not an integer value!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Int>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << "\t" <<val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}


/*! Returns the value of the boolean option with name \a fileName.
*  The arguments \a num and \a name are for debugging purposes only.
*  There is a convenience function Config_getBool() for this.
*/
bool     &Config::getBool(const std::string &name, const std::string &fileName, int num)
{
	auto & val = get(name, fileName, num);
	if (val.type() != boost::typeindex::type_id<Bool>())
	{
		Log::Error(fileName, num) << "Internal error: Requested option " << name << " not a boolean value!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Bool>(val);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		Log::Error(fileName, num) << "Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << "\t" << val.description << std::endl;
		std::exit(1);
	}
	return s.value;
}


/*! Returns the ConfigOption corresponding with \a name or 0 if
*  the option is not supported.
*/
Option 	 &Config::get	 (const std::string &name, const std::string &fileName, int num)
{
	for (auto & opt : Config::instance().options())
	{
		if (opt.name == name)
			return opt;
	}
	Log::Error(fileName, num) << "Requested unknown option " << name << "!" << std::endl;
    std::exit(1);

    return Config::instance().options().front();
}
/* @} */


std::string convertToComment(const std::string &doc, const std::string &user_comment)
{
	std::string result("#");
	if (!doc.empty())
	{
		std::string tmp = doc;
		boost::trim(tmp);
		auto p = tmp.begin();

		if (!tmp.empty() && (*p != '\n'))
			result+=" ";

		for (auto & c : tmp)
		while ((c=*p++))
		{
			if (c=='\n')
			{
				result+="\n#";
				if (*p && *p!='\n')
					result+=" ";
			}
			else result+=c;
		}
		result+='\n';
	}
	if (!user_comment.empty())
	{
		if (!result.empty())
			result+='\n';
		result+= user_comment;
	}
	return result;
}

void Config::check()
{
	// sanity check if all depends relations are valid
	for (auto & option : options())
	{
		if (!option.dependency.empty())
		{
			if (!hasOption(option.dependency))
			{
				Log::InternalError(__FILE__, __LINE__)
								<< "Config option '"
    		    			  	<< option.name
    							<< option.dependency
    							<< "' has invalid depends relation on unknown option '%s'\n";
    		    std::exit(1);
			}
		}
	}
}

void Config::writeTemplate(std::ostream &t,bool sl,bool upd)
{
	/* print first lines of user comment that were at the beginning of the file, might have special meaning for editors */
	if (!m_startComment.empty())
	{
		t << m_startComment << std::endl;
	}
	t << "# Doxyfile " << DoxyFrame::Version::String() << std::endl << std::endl;
	if (!sl)
	{
		t << convertToComment(m_header,"");
  	}
  	for (auto & option : options())
  	{
  		option.writeTemplate(t,sl,upd);
  	}
  	/* print last lines of user comment that were at the end of the file */
  	if (!m_userComment.empty())
  	{
  		t << "\n";
  		t << m_endComment << std::endl;
  	}
}

struct writeVisitor : boost::static_visitor<>
{
	std::ostream &t;
	Option & op;
	std::string &encoding;
	writeVisitor(std::ostream &os, Option &op, std::string& encoding) : t(os), op(op), encoding(encoding) {};

	void operator()(const Enum		 &e ) const;
	void operator()(const Bool 		 &b ) const;
	void operator()(const Int  		 &i ) const;
	void operator()(const String 	 &s ) const;
	void operator()(const Path 		 &p ) const;
	void operator()(const StringList &sl) const;
	void operator()(const PathList 	 &pl) const;

};


void writeVisitor::operator()(const Bool &b ) const
{
	t << " ";
	if (b.value)
		t << "YES";
	else
		t << "NO";
}

void writeVisitor::operator()(const Int& i) const
{
	t << " " << i.value;
}

void writeVisitor::operator()(const Path &s ) const
{
	// convert the string back to it original encoding
	t << s.value ;
}

inline std::string insertEscape(const std::string& value)
{
	std::string s2;
	s2.reserve(value.size());

	for (auto & c : value)
	{
		if ((c == ' ') || (c == '"') || (c == '"') || (c == '#'))
		{
			s2 += "\\";
			s2 += c;
		}
		else if (c == '\n')
			s2 += "\\n";
		else if (c == '\t')
			s2 += "\\t";
		else
			s2 += c;
	}
	return s2;
}

void writeVisitor::operator()(const String &s ) const
{
	// convert the string back to it original encoding
	std::string se = boost::locale::conv::from_utf(s.value, encoding);
	t << insertEscape(se);
}

void writeVisitor::operator()(const Enum &s ) const
{
	std::string se = boost::locale::conv::from_utf(s.value, encoding);
	t << insertEscape(se);
}

void writeVisitor::operator()(const PathList &l ) const
{
	bool first = true;

	for (auto & p : l.value)
  	{
		auto s = p.string();
		if (!first)
			t << "                        ";
		else
			if (s.empty()) t << " \\" << std::endl;

		first = false;
		t << s;
  }
}


void writeVisitor::operator()(const StringList &l ) const
{
	bool first = true;

	for (auto & s : l.value)
  	{

		if (!first)
			t << "                        ";
		else
			if (s.empty()) t << " \\" << std::endl;

		first = false;
		t << s;
  	}
}

struct writeTemplateVisitor : boost::static_visitor<>
{
	std::ostream &t;
	Option & op;
	bool sl;
	bool upd;

	writeTemplateVisitor(std::ostream &os, Option &opm, bool sl, bool upd) : t(os), op(op), sl(sl), upd(upd) {};

	void operator()(const Info		 &i ) const;
	void operator()(const Enum		 &i ) const;
	void operator()(const Bool 		 &b ) const;
	void operator()(const Int  		 &i ) const;
	void operator()(const String 	 &s ) const;
	void operator()(const Path 		 &p ) const;
	void operator()(const StringList &sl) const;
	void operator()(const PathList 	 &pl) const;

};

void writeTemplateVisitor::operator()(const Info & i) const
{
	if (!sl)
	{
		t << "\n";
	}
	t << "#---------------------------------------------------------------------------\n";
	t << "# " << op.doc << std::endl;
	t << "#---------------------------------------------------------------------------\n";
}

void writeTemplateVisitor::operator()(const StringList & i) const
{
  if (!sl)
  {
	  t << std::endl;
	  t << convertToComment(op.doc, op.user_comment);
	  t << std::endl;
  }
  else if (!op.user_comment.empty())
  {
	  t << convertToComment("", op.user_comment);
  	}

  	t << op.name << std::string(Option::max_option_length-op.name.length(), ' ') << "=";
  //	t << i.value;//TODO:
  	t << "\n";
}

void writeTemplateVisitor::operator()(const Enum & e) const
{
	if (!sl)
	{
		t << std::endl;
		t << convertToComment(op.doc, op.user_comment);
		t << std::endl;
	}
	else if (!op.user_comment.empty())
	{
		t << convertToComment("", op.user_comment);
	}
	t << op.name << std::string(Option::max_option_length-op.name.length(), ' ') << "=";
	t << e.value;
	t << "\n";
}

void writeTemplateVisitor::operator()(const String &s) const
{
	if (!sl)
	{
		t << std::endl;
		t << convertToComment(op.doc, op.user_comment);
		t << std::endl;
	}
	else if (!op.user_comment.empty())
	{
		t << convertToComment("", op.user_comment);
	}
	t << op.name << std::string(Option::max_option_length-op.name.length(), ' ') << "=";
	t << s.value;
	t << "\n";
}

void writeTemplateVisitor::operator()(const Int &s) const
{
	if (!sl)
  	{
		t << std::endl;
		t << convertToComment(op.doc, op.user_comment);
    	t << std::endl;
  	}
	else if (!op.user_comment.empty())
	{
		t << convertToComment("", op.user_comment);
	}
	t << op.name << std::string(Option::max_option_length-op.name.length(), ' ') << "=";

	t << s.value;

	t << "\n";
}

void writeTemplateVisitor::operator()(const Bool &s) const
{
	if (!sl)
	{
		t << std::endl;
		t << convertToComment(op.doc, op.user_comment);
		t << std::endl;
	}
	else if (!op.user_comment.empty())
	{
		t << convertToComment("", op.user_comment);
	}
	t << op.name << std::string(Option::max_option_length-op.name.length(), ' ') << "=";

	t << s.value;

	t << "\n";
}

struct assignVisitor : boost::static_visitor<>
{
	std::string value;
	Option & op;
	assignVisitor(const std::string &value, Option &op) : value(value), op(op) {}

	void operator()(Info		 &i );
	void operator()(Enum		 &i );
	void operator()(Bool 		 &b );
	void operator()(Int  		 &i );
	void operator()(String 	 &s );
	void operator()(Path 		 &p );
	void operator()(StringList &sl);
	void operator()(PathList 	 &pl);
};

void assignVisitor::operator()( Int& i)
{
	op.set = true;

	bool ok = true;
	int val;
	try {
		val = std::stoi(value);
		op.set = true;
	}
	catch (std::logic_error& ) {ok = false;};

	if (!ok || (val < i.min) || (val > i.max))
	{
		std::cerr << "argument `"  << i.value
				<< "' for option " << op.name
				<<" is not a valid number in the range [" << i.min
				<<".."<< i.max
				<< "]!\n";

		if (i.default_value)
		{
			std::cerr << "Using the default: " << i.value << "!\n";
			i.value = *i.default_value;
			op.set = true;
		}
		else
		{
			std::cerr  << "No default value given, aborting..." << std::endl;
			std::exit(1);
		}
	}
	else
	{
		i.value = val;
		op.set = true;
	}

}

void assignVisitor::operator()(Bool& i)
{
	std::string val = boost::trim_copy(value);
	boost::algorithm::to_lower(val);

	if (val=="yes" || val=="true" || val=="1" || val=="all")
	{
		i.value = true;
		op.set = true;
	}
	else if (val=="no" || val=="false" || val=="0" || val=="none")
	{
		i.value = false;
		op.set = true;
	}
	else
	{
		std::cerr << "argument `" << val
				  << "' for option " << op.name
				  << " is not a valid boolean value\n";

		if (i.default_value)
		{
			std::cerr  << "Using the default: " << (*i.default_value ? "YES" : "NO") << "!"  << std::endl;
			i.value = *i.default_value;
			op.set = true;

		}
		else
		{
			std::cerr  << "No default value given, aborting..." << std::endl;
			std::exit(1);
		}
	}

}


std::string Recode(
    const std::string &str,
    const std::string &fromEncoding,
    const std::string &toEncoding)
{
	std::string inputEncoding = fromEncoding;
	std::string outputEncoding = toEncoding;
	if (inputEncoding. empty() ||
		outputEncoding.empty() ||
		(inputEncoding==outputEncoding))
					return str;

	//int inputSize=str.length();
//	int outputSize=inputSize*4+1;

	std::string output;

	try {
		output = boost::locale::conv::between(str, inputEncoding, outputEncoding);
	}
	catch (boost::locale::conv::conversion_error & ce)
	{
		std::cerr << "Error: failed to translate characters from " << inputEncoding
				  << " to " << outputEncoding
				  << ": " << ce.what() << "\n";
		std::exit(1);
	}
	return output;
}
///Checks if config has an option, including disabled, obsolete and unknown objects.
bool Config::has(const std::string& name)
{
	auto it = std::find_if(m_options .begin(), m_options .end(), [&](const Option &op){return op .name == name;}); if (it != m_options .end()) return true;
		 it = std::find_if(m_obsolete.begin(), m_obsolete.end(), [&](const Option &op){return op .name == name;}); if (it != m_obsolete.end()) return true;
		 it = std::find_if(m_disabled.begin(), m_disabled.end(), [&](const Option &op){return op .name == name;}); if (it != m_disabled.end()) return true;


//	auto it2 = std::find_if(m_unknown .begin(), m_unknown .end(), [&](const RawOption &op){return op .name == name;}); if (it != m_unknown .end()) return true;

	return m_unknown.count(name) > 0;
}

bool Config::hasOption	(const std::string& name)
{
	auto it = std::find_if(m_options .begin(), m_options .end(), [&](const Option &op){return op .name == name;});
	return it != m_options.end();
}

bool Config::hasObsolete(const std::string& name)
{
	auto it = std::find_if(m_obsolete .begin(), m_obsolete .end(), [&](const Option &op){return op .name == name;});
	return it != m_obsolete.end();
}


bool Config::hasDisabled(const std::string& name)
{
	auto it = std::find_if(m_disabled .begin(), m_disabled .end(), [&](const Option &op){return op .name == name;});
	return it != m_disabled.end();
}

bool Config::hasUnknown(const std::string& name)
{
	return m_unknown.count(name) > 0;
}

void Option::writeTemplate(std::ostream& t, bool sl, bool spd)
{
	writeTemplateVisitor vis(t, *this, sl, spd);
}


void Config::append(const RawConfig & rc)
{
	auto &enc = rc.at("DOXYFILE_ENCODING");


	if (enc.data.size() == 0)
		Warn(enc.file_name, enc.line_nr) << "DOXYFILE_ENCODING must be a single string, e.g. 'UTF-8', but is empty. 'UTF-8' will be used." << std::endl;
	else if (enc.data.size() > 1)
	{
		Warn(enc.file_name, enc.line_nr) << "DOXYFILE_ENCODING must be a single string, e.g. 'UTF-8', but has multiple values defined. First element will be used, which is: '" << enc.data[0] << "'" << std::endl;
		m_encoding = enc.data[0];
	}
	else
		m_encoding = enc.data[0];


	this->m_startComment += to_utf<char>(rc.startComment, m_encoding);
	this->m_endComment 	 += to_utf<char>(rc.endComment, 	m_encoding);

	for (auto & p : rc)
		insert(p.first, p.second);


}
void Config::insert(const std::string name, const RawOption & ro)
{
	if (has(name))
	{

	}
	else
	{
		auto & val = this->m_unknown[name];


	}

}

}
}


