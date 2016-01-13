/**
 * @file   config.cpp
 * @date   12.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */


#include <config.hpp>
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
std::string &getString(const std::string &name, const std::string &fileName, int num)
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
boost::filesystem::path &getPath(const std::string &name, const std::string &fileName, int num)
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
std::vector<std::string> &getStringList(const std::string &name, const std::string &fileName, int num)
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
std::vector<boost::filesystem::path> &getPathList(const std::string &name, const std::string &fileName, int num)
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
std::string  &getEnum(const std::string &name, const std::string &fileName, int num)
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
int &getInt(const std::string &name, const std::string &fileName ,int num)
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
bool     &getBool(const std::string &name, const std::string &fileName, int num)
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
Option 	 &get	 (const std::string &name, const std::string &fileName, int num)
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

	return boost::get<String>(m_options.back().entry);
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
StringList   &Config::addPathList(const std::string &name, const std::string &doc)
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
	op.entry = boost::none;
	op.name = name;

	m_options.push_back(std::move(op));

	return m_options.back().entry;
}

/*! Adds an option that has been disabled at compile time. */
Option &Config::addDisabled(const std::string &name)
{
	Option op;
	op.entry = boost::none;
	op.name = name;

	m_options.push_back(std::move(op));

	return m_options.back().entry;
}
/*! @} */

std::string Config::convertToComment(const std::string &s, const std::string &u)
{
	std::string result("#");
	if (!s.empty())
	{
		std::string tmp = s;
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
	if (!u.empty())
	{
		if (!result.empty())
			result+='\n';
		result+= u;
	}
	return result;
}

void Config::init()
{
  ConfigOptionAbstract option;

  // sanity check if all depends relations are valid
  for (auto & option : range())
  {
    std::string depName = option.dependsOn();
    if (!depName.empty())
    {
      ConfigOptionAbstract * opt = Config::instance().get(depName);
      if (opt==0)
      {
    	  std::cerr << "Config option '"
    			  	<< option.name()
					<< depName
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
    t << takeStartComment() << endl;
  }
  t << "# Doxyfile " << versionString << endl << endl;
  if (!sl)
  {
	  t << Config::convertToComment(m_header,"");
  }
  for (auto & option : range())
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

void Config::convertStrToVal()
{
	for (auto & option : range())
	{
		option.convertStrToVal();
	}
}

void ConfigOptionAbstract::write(std::ostream &t,bool v)
{
  t << " ";
  if (v) t << "YES"; else t << "NO";
}

void ConfigOptionAbstract::write(std::ostream &t,int i)
{
  t << " " << i;
}

void ConfigOptionAbstract::write(std::ostream &t, const std::string &s)
{
	bool needsEscaping=false;
	// convert the string back to it original encoding
	std::string se = Config::configStringRecode(s,"UTF-8",m_encoding);
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

void ConfigOptionAbstract::write(std::ostream &t, const std::vector<std::string> &l)
{
	bool first = true;

	for (auto & s : l)
  	{

		if (!first)
			t << "                        ";
		else
			if (s.empty()) t << " \\" << endl;

		first = false;
		write(t,s);
  }
}


void ConfigInt::convertStrToVal()
{
  if (!m_valueString.empty())
  {
    bool ok = true;
    int val;
    try {
    	 val = std::stoi(m_valueString);
    }
    catch (std::logic_error& ) {ok = false;};

    if (!ok || val<m_minVal || val>m_maxVal)
    {
      std::cerr << "argument `" << m_valueString
    		  	<< "' for option " << m_name
				<<" is not a valid number in the range [" << m_minVal
				<<".."<< m_maxVal
				<< "]!\n"
                << "Using the default: %d!\n"<<  m_value;
    }
    else
    {
      m_value=val;
    }
  }
}

void ConfigBool::convertStrToVal()
{
	std::string val = boost::trim(m_valueString);
	boost::algorithm::to_lower(val);
	if (!val.empty())
	{
		if (val=="yes" || val=="true" || val=="1" || val=="all")
		{
			m_value = true;
		}
		else if (val=="no" || val=="false" || val=="0" || val=="none")
		{
			m_value = false;
		}
		else
		{
			std::cerr << "argument `" << m_valueString
					  << "' for option " << m_name
					  << " is not a valid boolean value\n"
					  << "Using the default: " << (m_value ? "YES" : "NO") << "!\n";
		}
  }
}

std::string &Config::getString(const std::string &name, const std::string &fileName,int num) const
{
	auto itr = std::find_if(m_dict.begin(), m_dict.end(),
							[&](ConfigOptionAbstract &coa){return coa.m_name == name;});

	if (itr != m_dict.end())
	{
		std::cerr 	<< fileName << "<" << num
					<< ">: Internal error: Requested unknown option " << name ;
		std::exit(1);
	}
	else if (itr->type() != boost::typeindex::type_id<ConfigString>())
	{
		std::cerr << fileName << "<" << num
				  << ">: Internal error: Requested option " << name << " not of string type!\n";
		std::exit(1);
	}

	return boost::get<ConfigString>(*itr).m_value;
}

std::vector<std::string> &Config::getList(const std::string &name, const std::string &fileName,int num) const
{
	auto itr = std::find_if(m_dict.begin(), m_dict.end(),
							[&](ConfigOptionAbstract &coa){return coa.m_name == name;});

	if (itr != m_dict.end())
	{
		std::cerr 	<< fileName << "<" << num
					<< ">: Internal error: Requested unknown option " << name ;
		std::exit(1);
	}
	else if (itr->type() != boost::typeindex::type_id<ConfigList>())
	{
		std::cerr << fileName << "<" << num
				  << ">: Internal error: Requested option " << name << " not of list type!\n";
		std::exit(1);
	}
	return boost::get<ConfigList>(*itr).m_value;
}

std::string &Config::getEnum(const std::string &name, const std::string &fileName,int num) const
{
	auto itr = std::find_if(m_dict.begin(), m_dict.end(),
							[&](ConfigOptionAbstract &coa){return coa.m_name == name;});

	if (itr != m_dict.end())
	{
		std::cerr 	<< fileName << "<" << num
					<< ">: Internal error: Requested unknown option " << name ;
		std::exit(1);
	}
	else if (itr->type() != boost::typeindex::type_id<ConfigEnum>())
	{
		std::cerr << fileName << "<" << num
				  << ">: Internal error: Requested option " << name << " not of enum type!\n";
		std::exit(1);
	}
	return boost::get<ConfigEnum>(*itr).m_value;
}

int &Config::getInt(const std::string &name, const std::string &fileName,int num) const
{
	auto itr = std::find_if(m_dict.begin(), m_dict.end(),
							[&](ConfigOptionAbstract &coa){return coa.m_name == name;});

	if (itr != m_dict.end())
	{
		std::cerr 	<< fileName << "<" << num
					<< ">: Internal error: Requested unknown option " << name ;
		std::exit(1);
	}
	else if (itr->type() != boost::typeindex::type_id<ConfigInt>())
	{
		std::cerr << fileName << "<" << num
				  << ">: Internal error: Requested option " << name << " not of integer type!\n";
		std::exit(1);
	}
	return boost::get<ConfigInt>(*itr).m_value;
}

bool &Config::getBool(const std::string &name, const std::string &fileName,int num) const
{
	auto itr = std::find_if(m_dict.begin(), m_dict.end(),
							[&](ConfigOptionAbstract &coa){return coa.m_name == name;});

	if (itr != m_dict.end())
	{
		std::cerr 	<< fileName << "<" << num
					<< ">: Internal error: Requested unknown option " << name ;
		std::exit(1);
	}
	else if (itr->type() != boost::typeindex::type_id<ConfigBool>())
	{
		std::cerr << fileName << "<" << num
				  << ">: Internal error: Requested option " << name << " not of boolean type!\n";
		std::exit(1);
	}
	return boost::get<ConfigBool>(*itr).m_value;
}

/* ------------------------------------------ */

void ConfigInfo::writeTemplate(std::ostream &t, bool sl,bool)
{
	if (!sl)
	{
		t << "\n";
	}
	t << "#---------------------------------------------------------------------------\n";
	t << "# " << m_doc << endl;
	t << "#---------------------------------------------------------------------------\n";
}

void ConfigList::writeTemplate(std::ostream &t,bool sl,bool)
{
  if (!sl)
  {
    t << endl;
    t << Config::convertToComment(m_doc, m_userComment);
    t << endl;
  }
  else if (!m_userComment.empty())
  {
	  t << Config::convertToComment("", m_userComment);
  }

  t << m_name << std::string(ConfigOption::max_option_length-m_name.length(), ' ') << "=";
  write(t, m_value);
  t << "\n";
}

void ConfigEnum::writeTemplate(std::ostream &t,bool sl,bool)
{
  if (!sl)
  {
    t << endl;
    t << Config::convertToComment(m_doc, m_userComment);
    t << endl;
  }
  else if (!m_userComment.empty())
  {
    t << Config::convertToComment("", m_userComment);
  }
  t << m_name << std::string(ConfigOption::max_option_length-m_name.length(), ' ') << "=";
  write(t,m_value);
  t << "\n";
}

void ConfigString::writeTemplate(std::ostream &t,bool sl,bool)
{
  if (!sl)
  {
    t << endl;
    t << Config::convertToComment(m_doc, m_userComment);
    t << endl;
  }
  else if (!m_userComment.empty())
  {
    t << Config::convertToComment("", m_userComment);
  }
  t << m_name << std::string(ConfigOption::max_option_length-m_name.length(), ' ') << "=";
  write(t,m_value);
  t << "\n";
}

void ConfigInt::writeTemplate(std::ostream &t,bool sl,bool upd)
{
  if (!sl)
  {
    t << endl;
    t << Config::convertToComment(m_doc, m_userComment);
    t << endl;
  }
  else if (!m_userComment.empty())
  {
    t << Config::convertToComment("", m_userComment);
  }
  t << m_name << std::string(ConfigOption::max_option_length-m_name.length(), ' ') << "=";
  if (upd && !m_valueString.empty())
  {
	  write(t,m_valueString);
  }
  else
  {
	  write(t,m_value);
  }
  t << "\n";
}

void ConfigBool::writeTemplate(std::ostream &t,bool sl,bool upd)
{
  if (!sl)
  {
    t << endl;
    t << Config::convertToComment(m_doc, m_userComment);
    t << endl;
  }
  else if (!m_userComment.empty())
  {
    t << Config::convertToComment("", m_userComment);
  }
  t << m_name << std::string(ConfigOption::max_option_length-m_name.length(), ' ') << "=";
  if (upd && !m_valueString.empty())
  {
	  write(t,m_valueString);
  }
  else
  {
	  write(t,m_value);
  }
  t << "\n";
}

std::string Config::configStringRecode(
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

	int inputSize=str.length();
	int outputSize=inputSize*4+1;

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


}
}
