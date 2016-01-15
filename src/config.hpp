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

#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <regex>
#include <ostream>
#include <istream>
#include <boost/range/iterator_range.hpp>
#include <boost/variant.hpp>
#include <boost/type_index.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <boost/property_tree/ptree.hpp>

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

	static constexpr std::size_t max_option_length = 23;

	using Entry = boost::variant<boost::none_t,
			StringList, PathList,
			String, Path, Enum,
			Bool, Int, Info>;

	Entry entry = boost::none;

	Option & operator= (const std::string & value) {this->assign(value); return *this;};
	Option & operator+=(const std::string & value) {this->append(value); return *this;};
	void assign(const std::string & st);
	void append(const std::string & st);
	void clear();
	void writeTemplate(std::ostream &t, bool sl,bool);
	bool isList() const;
};

inline bool operator==(const Option& lhs, const Option &rhs) {return lhs.name == rhs.name;};
inline bool operator!=(const Option& lhs, const Option &rhs) {return lhs.name != rhs.name;};

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

	bool ignoreUnknown() const
	{
		return true;
	}

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
    bool parseString(const std::string &fn,	const std::string &str,	bool upd = false);

    /*! Parse a configuration file with name \a fn.
     *  \returns TRUE if successful, FALSE if the file could not be 
     *  opened or read.
     */ 
    bool parse(const std::string &fn,	bool upd = false);


    /*! Append user start comment
     */
    void appendStartComment(const std::string &u)
    {
      m_startComment += u;
    }
    /*! Append user comment
     */
    void appendUserComment(const std::string &u)
    {
      m_userComment += u;
    }
    /*! Take the user start comment and reset it internally
     *  \returns user start comment
     */
    std::string takeStartComment()
    {
      std::string result = std::move(m_startComment);
      m_startComment = "";
      boost::replace_all(result, "\r", "");
      return result;
    }
    /*! Take the user comment and reset it internally
     *  \returns user comment
     */
    std::string takeUserComment()
    {
      std::string result = std::move(m_userComment);
      m_userComment = "";
      boost::replace_all(result, "\r", "");

      return result;
    }

    Info   		&addInfo	(const std::string &name, const std::string &doc);
    String 		&addString	(const std::string &name, const std::string &doc);
    Enum 		&addEnum	(const std::string &name, const std::string &doc, const std::string &defVal);
    StringList  &addStringList(const std::string &name, const std::string &doc);
    PathList	&addPathList(const std::string &name, const std::string &doc);
    Int    		&addInt		(const std::string &name, const std::string &doc, int minVal,int maxVal,int defVal);
    Bool   		&addBool	(const std::string &name, const std::string &doc,bool defVal);
    Option 		&addObsolete(const std::string &name);
    Option 		&addDisabled(const std::string &name);

    std::string 				&getString(const std::string &name, const std::string &fileName = "", int num = -1);
    boost::filesystem::path 	&getPath  (const std::string &name, const std::string &fileName = "", int num = -1);
    std::vector<std::string>	&getStringList(const std::string &name, const std::string &fileName = "", int num = -1);
    std::vector<boost::filesystem::path> &getPathList(const std::string &name, const std::string &fileName = "", int num = -1);
    std::string  				&getEnum  (const std::string &name, const std::string &fileName = "", int num = -1);
    int      					&getInt   (const std::string &name, const std::string &fileName = "", int num = -1);
    bool     					&getBool  (const std::string &name, const std::string &fileName = "", int num = -1);
    Option 	 					&get	  (const std::string &name, const std::string &fileName = "", int num = -1);


    Config() {}
    ~Config() {}

	bool has(const std::string& name);
    bool hasOption	(const std::string& name);
    bool hasObsolete(const std::string& name);
    bool hasDisabled(const std::string& name);
    bool hasUnknown (const std::string& name);

    bool isUpdating() const;

    Option & includePath();
  protected:


    static void addConfigOptions(Config &cfg);
  private:
    void checkFileName(const std::string &);
    std::vector<Option> m_options ;
    std::vector<Option> m_obsolete;
    std::vector<Option> m_disabled;
    std::vector<Option> m_unknown ;
    static std::unique_ptr<Config> m_instance;

    std::string m_startComment;
    std::string m_userComment;
    std::string m_header;
};

inline std::string 				&getString(const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getString(name, fileName, num);}
inline boost::filesystem::path 	&getPath  (const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getPath(name, fileName, num);};
inline std::vector<std::string>	&getStringList(const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getStringList(name, fileName, num);};
inline std::vector<boost::filesystem::path> &getPathList(const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getPathList(name, fileName, num);};
inline std::string  			&getEnum  (const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getEnum(name, fileName, num);};
inline int      				&getInt   (const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getInt (name, fileName, num);};
inline bool     				&getBool  (const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().getBool(name, fileName, num);};
inline Option 	 				&get	  (const std::string &name, const std::string &fileName = "", int num = -1) {return Config::instance().get	  (name, fileName, num);};

inline Info   		&addInfo  	(const std::string &name, const std::string &doc) 	{return Config::instance().addInfo(name, doc);}
inline String 	 	&addString	(const std::string &name, const std::string &doc)	{return Config::instance().addString(name, doc);}
inline Enum 		&addEnum	(const std::string &name, const std::string &doc, const std::string &defVal) {return Config::instance().addEnum(name, doc, defVal); }
inline StringList  	&addStringList(const std::string &name, const std::string &doc)	{return Config::instance().addStringList(name, doc);}
inline PathList  	&addPathList(const std::string &name, const std::string &doc)	{return Config::instance().addPathList(name, doc);}
inline Int    		&addInt		(const std::string &name, const std::string &doc, int minVal,int maxVal,int defVal) {return Config::instance().addInt(name, doc, minVal, maxVal, defVal);}
inline Bool   	 	&addBool	(const std::string &name, const std::string &doc,bool defVal) {return Config::instance().addBool(name, doc, defVal);}
inline Option 	 	&addObsolete(const std::string &name) {return Config::instance().addObsolete(name);}
inline Option 	 	&addDisabled(const std::string &name) {return Config::instance().addDisabled(name);}

std::string Recode(
        const std::string &str,
        const std::string &fromEncoding,
        const std::string &toEncoding);

std::string convertToComment(const std::string &s, const std::string &u);

}
}




#endif
