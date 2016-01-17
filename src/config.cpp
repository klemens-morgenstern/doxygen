/**
 * @file   config.cpp
 * @date   12.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */


#include <config.hpp>
#include <version.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/type_index.hpp>
#include <boost/locale.hpp>

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
	if (val.entry.type() != boost::typeindex::type_id<String>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not a string!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<String>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<Path>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not a path!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Path>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<StringList>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not a string list!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<StringList>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<PathList>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not a path list!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<PathList>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<Enum>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not an enumerator!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Enum>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<Int>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not an integer value!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Int>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
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
	if (val.entry.type() != boost::typeindex::type_id<Bool>())
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not a boolean value!" << std::endl;
		std::exit(1);
	}

	auto &s = boost::get<Bool>(val.entry);
	if (val.set)
		return s.value;
	else if (s.default_value)
		return *s.default_value;
	else
	{
		std::cerr << fileName << "<" << num << ">: Internal error: Requested option " << name << " not set!" << std::endl;
		if (!val.description.empty())
			std::cerr << val.description << std::endl;
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
    std::cerr << fileName << "<" << num << ">: Internal error: Requested unknown option " << name << "!" << std::endl;
    std::exit(1);

    return Config::instance().options().front();
}
/* @} */

/*!
 *  @name Adding configuration options.
 *  @{
 */

/*! Starts a new configuration section with \a name and description \a doc.
 *  \returns An object representing the option.
 */
Info   &Config::addInfo(const std::string &name, const std::string &doc)
{
	Option op;
	op.entry = Info();
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<Info>(m_options.back().entry);
}

/*! Adds a new string option with \a name and documentation \a doc.
 *  \returns An object representing the option.
 */
String &Config::addString(const std::string &name, const std::string &doc)
{
	Option op;
	op.entry = String();
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<String>(m_options.back().entry);
}

/*! Adds a new enumeration option with \a name and documentation \a doc
 *  and initial value \a defVal.
 *  \returns An object representing the option.
 */
Enum &Config::addEnum(const std::string &name, const std::string &doc, const std::string &defVal)
{
	Option op;
	String s;
	s.default_value = defVal;
	op.entry = std::move(s);
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<Enum>(m_options.back().entry);
}

/*! Adds a new string option with \a name and documentation \a doc.
 *  \returns An object representing the option.
 */
StringList   &Config::addStringList(const std::string &name, const std::string &doc)
{
	Option op;
	StringList s;
	op.entry = std::move(s);
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<StringList>(m_options.back().entry);;
}

/*! Adds a new string option with \a name and documentation \a doc.
 *  \returns An object representing the option.
 */
PathList   &Config::addPathList(const std::string &name, const std::string &doc)
{
	Option op;
	PathList s;
	op.entry = std::move(s);
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<PathList>(m_options.back().entry);;
}

/*! Adds a new integer option with \a name and documentation \a doc.
 *  The integer has a range between \a minVal and \a maxVal and a
 *  default value of \a defVal.
 *  \returns An object representing the option.
 */
Int    &Config::addInt(const std::string &name, const std::string &doc,
			   int minVal,int maxVal,int defVal)
{
	Option op;
	Int s;
	s.max = maxVal;
	s.min = minVal;
	s.default_value = defVal;
	op.entry = std::move(s);
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<Int>(m_options.back().entry);;
}



/*! Adds a new boolean option with \a name and documentation \a doc.
 *  The boolean has a default value of \a defVal.
 *  \returns An object representing the option.
 */
Bool   &Config::addBool(const std::string &name,
				const std::string &doc,
				bool defVal)
{
	Option op;
	Bool s;
	s.default_value = defVal;
	op.entry = std::move(s);
	op.name = name;
	op.doc  = doc;

	m_options.push_back(std::move(op));

	return boost::get<Bool>(m_options.back().entry);;
}

/*! Adds an option that has become obsolete. */
Option &Config::addObsolete(const std::string &name)
{
	Option op;
	op.entry = boost::blank();
	op.name = name;

	m_options.push_back(std::move(op));

	return m_options.back();
}

/*! Adds an option that has been disabled at compile time. */
Option &Config::addDisabled(const std::string &name)
{
	Option op;
	op.entry = boost::blank();
	op.name = name;

	m_options.push_back(std::move(op));

	return m_options.back();
}
/*! @} */

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

void Config::init()
{
	// sanity check if all depends relations are valid
	for (auto & option : options())
	{
		if (!option.dependency.empty())
		{
			if (!hasOption(option.dependency))
			{
				std::cerr << "Config option '"
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
		t << takeStartComment() << std::endl;
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
  		t << takeUserComment();
  	}
}

struct writeVisitor : boost::static_visitor<>
{
	std::ostream &t;
	Option & op;
	writeVisitor(std::ostream &os, Option &op) : t(os), op(op) {};

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
	bool needsEscaping = false;
	// convert the string back to it original encoding
	std::string se = s.value.string();
	if (!se.empty())
	{
		auto itr = se.begin();
		t << " ";
		char c;

		while ((se.end()!=++itr)!=0 && !needsEscaping)
			needsEscaping = (c==' ' || c=='\n' || c=='\t' || c=='"' || c=='#');
		if (needsEscaping)
		{
			t << "\"";
			auto p=se.data();
			while (*p)
			{
				if (*p==' ' && *(p+1)=='\0') break; // skip inserted space at the end
				if (*p=='"') t << "\\"; // escape quotes
				t << *p++;
			}
			t << "\"";
		}
		else
		{
			t << se;
		}
	}}

void writeVisitor::operator()(const String &s ) const
{
	bool needsEscaping = false;
	// convert the string back to it original encoding
	std::string se = Recode(s.value, "UTF-8", op.encoding);
	if (!se.empty())
	{
		auto itr = se.begin();
		t << " ";
		char c;

		while ((se.end()!=++itr)!=0 && !needsEscaping)
		{
			needsEscaping = (c==' ' || c=='\n' || c=='\t' || c=='"' || c=='#');
		}
		if (needsEscaping)
		{
			t << "\"";
			auto p=se.data();
			while (*p)
			{
				if (*p==' ' && *(p+1)=='\0') break; // skip inserted space at the end
				if (*p=='"') t << "\\"; // escape quotes
				t << *p++;
			}
			t << "\"";
		}
		else
		{
			t << se;
		}
	}
}

void writeVisitor::operator()(const Enum &s ) const
{
	bool needsEscaping = false;
	// convert the string back to it original encoding
	std::string se = Recode(s.value, "UTF-8", op.encoding);
	if (!se.empty())
	{
		auto itr = se.begin();
		t << " ";
		char c;

		while ((se.end()!=++itr)!=0 && !needsEscaping)
			needsEscaping = (c==' ' || c=='\n' || c=='\t' || c=='"' || c=='#');
		if (needsEscaping)
		{
			t << "\"";
			auto p=se.data();
			while (*p)
			{
				if (*p==' ' && *(p+1)=='\0') break; // skip inserted space at the end
				if (*p=='"') t << "\\"; // escape quotes
				t << *p++;
			}
			t << "\"";
		}
		else
		{
			t << se;
		}
	}
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
		 it = std::find_if(m_unknown .begin(), m_unknown .end(), [&](const Option &op){return op .name == name;}); if (it != m_unknown .end()) return true;

	return false;
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
	auto it = std::find_if(m_unknown .begin(), m_unknown .end(), [&](const Option &op){return op .name == name;});
	return it != m_unknown.end();
}


}
}

void DoxyFrame::Config::Option::writeTemplate(std::ostream& t, bool sl, bool spd)
{
	writeTemplateVisitor vis(t, *this, sl, spd);
}
