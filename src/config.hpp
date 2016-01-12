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
#include <boost/range/iterator_range.hpp>
#include <boost/variant.hpp>

namespace DoxyFrame
{

/** Abstract base class for any configuration option. */
struct ConfigOptionAbstract
{
	ConfigOptionAbstract(const std::string & name = "", const std::string &doc = "")
			: m_name(name), m_doc(doc)
	{}

    std::string m_spaces{' ', 40};
    std::string m_name;
    std::string m_doc;
    std::string m_dependency;
    std::string m_encoding;
    std::string m_userComment;


    void write(std::ostream &t, bool v);
    void write(std::ostream &t, int i);
    void write(std::ostream &t, const std::string &s);
    void write(std::ostream &t, const std::vector<std::string> &l);

    void writeTemplate(std::ostream &t,bool sl,bool upd) {}

};


/** Class respresenting a list type option.
 */
struct ConfigList : public ConfigOptionAbstract
{
    enum WidgetType { String, File, Dir, FileAndDir };
    ConfigList(const std::string &name,const std::string &doc) :
    	ConfigOptionAbstract(name, doc)
    {
      m_widgetType = String;
    }

    std::vector<std::string> m_value;
    WidgetType m_widgetType;

    void writeTemplate(std::ostream &t,bool sl,bool);
    void substEnvVars();

};


/** Section marker for grouping the configuration options.
 */
struct ConfigInfo : public ConfigOptionAbstract
{
    ConfigInfo(const std::string &name,const std::string &doc)
      : ConfigOptionAbstract(name, doc) {}

    void writeTemplate(std::ostream &t, bool sl,bool);
    void substEnvVars() {}
};


/** Class representing an enum type option.
 */
struct ConfigEnum : public ConfigOptionAbstract
{
    ConfigEnum(const std::string &name,const std::string & doc,const std::string &defVal)
      : ConfigOptionAbstract(name, doc), m_value(defVal), m_defValue(defVal)
    {
    }
    void writeTemplate(std::ostream &t,bool sl,bool);

    std::vector<std::string> m_valueRange;
    std::string m_value;
    std::string m_defValue;
};

/** Class representing a string type option.
 */
struct ConfigString : public ConfigOptionAbstract
{
    enum WidgetType { String, File, Dir, Image };
    ConfigString(const std::string &name,const std::string &doc)
      : ConfigOptionAbstract(name, doc), m_widgetType(String)
    {
    }
    void writeTemplate(std::ostream &t,bool sl,bool);

    std::string m_value;
    std::string m_defValue;
    WidgetType m_widgetType;
};

/** Class representing an integer type option.
 */
struct ConfigInt : public ConfigOptionAbstract
{
    ConfigInt(const std::string &name, const std::string &doc, int minVal, int maxVal, int defVal)
      : ConfigOptionAbstract(name, doc), m_value(defVal), m_defValue(defVal), m_minVal(minVal), m_maxVal(maxVal)
    {
    }
    std::string &valueString() { return m_valueString; }
    int &value() { return m_value; }
    int minVal() const { return m_minVal; }
    int maxVal() const { return m_maxVal; }
    void convertStrToVal();
    void substEnvVars();
    void writeTemplate(std::ostream &t,bool sl,bool upd);
    void init() { m_value = m_defValue; }
  private:
    int m_value;
    int m_defValue;
    int m_minVal;
    int m_maxVal;
    std::string m_valueString;
};

/** Class representing a Boolean type option.
 */
struct ConfigBool : public ConfigOptionAbstract
{
    ConfigBool(const std::string &name,const std::string &doc,bool defVal)
      : ConfigOptionAbstract(name, doc), m_value(defVal), m_defValue(defVal)
    {
    }
    std::string &valueString() 	{ return m_valueString; }
    bool &value() 				{ return m_value; }
    void convertStrToVal();
    void substEnvVars();
    void setValueString(const std::string &v) { m_valueString = v; }
    void writeTemplate(std::ostream &t,bool sl,bool upd);
    void init() { m_value = m_defValue; }
  private:
    bool m_value;
    bool m_defValue;
    std::string m_valueString;
};

/** Section marker for obsolete options
 */
struct ConfigObsolete : public ConfigOptionAbstract
{
    ConfigObsolete(const std::string &name) : ConfigOptionAbstract(name)
    {}
    void substEnvVars() {}
};

/** Section marker for compile time optional options
 */
struct ConfigDisabled : public ConfigOptionAbstract
{
    ConfigDisabled(const std::string &name) : ConfigOptionAbstract(name)
    {}
    void substEnvVars() {}
};

struct ConfigOption : boost::variant<ConfigList, ConfigInfo, ConfigEnum, ConfigString, ConfigInt, ConfigBool, ConfigObsolete, ConfigDisabled>
{

    std::string dependsOn() const
    {
    	dependsOnVis vis;
    	return boost::apply_visitor(vis, *this);
    }



    std::string name() const
    {
    	nameVis vis;
    	return boost::apply_visitor(vis, *this);
    }


    void writeTemplate(std::ostream &t,bool sl,bool upd)
    {
    	writeTemplateVis vis;
    	vis.os = &t;
    	vis.sl = sl;
    	vis.upd= upd;
    	boost::apply_visitor(vis, *this);
    }

    void convertStrToVal()
    {
    	convertStrToValVis vis;
    	boost::apply_visitor(vis, *this);
    };

    static constexpr std::size_t max_option_length = 23;
private:
	struct writeTemplateVis : boost::static_visitor<>
	{
		std::ostream *os; bool sl; bool upd;
		template<typename T>
		void operator()(T& value) {value.writeTemplate(*os, sl, upd);}
	} ;
	struct convertStrToValVis : boost::static_visitor<>
	{
		void operator()(ConfigOptionAbstract &value) {};
		void operator()(ConfigInt & ce)  {ce.convertStrToVal();};
		void operator()(ConfigBool & ce) {ce.convertStrToVal();};
	} ;
    struct nameVis : boost::static_visitor<std::string>
    {
		template<typename T>
    	const std::string & operator()(const T& value) {return value.m_name;}
    };
	struct dependsOnVis: boost::static_visitor<std::string>
	{
		template<typename T>
		const std::string & operator()(const T& value) {return value.m_dependency;};
	};
};

// some convenience macros for access the config options
#define DOXY_CONFIG_GET_STRING(val)  Config::getString	(val, __FILE__,__LINE__)
#define DOXY_CONFIG_GET_INT(val)     Config::getInt		(val, __FILE__,__LINE__)
#define DOXY_CONFIG_GET_LIST(val)    Config::getList	(val, __FILE__,__LINE__)
#define DOXY_CONFIG_GET_ENUM(val)    Config::getEnum	(val, __FILE__,__LINE__)
#define DOXY_CONFIG_GET_BOOL(val)    Config::getBool	(val, __FILE__,__LINE__)

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
      if (m_instance==nullptr) m_instance = std::unique_ptr<Config>();
      return *m_instance;
    }
    /*! Delete the instance */
    static void deleteInstance()
    {
      m_instance = nullptr;
    }
    
    /*! Returns an iterator that can by used to iterate over the 
     *  configuration options.
     */
    boost::iterator_range<typename std::vector<ConfigOption>::iterator> range()
    {
      return boost::make_iterator_range(m_options);
    }

    /*! 
     *  @name Getting configuration values.
     *  @{
     */

    /*! Returns the value of the string option with name \a fileName. 
     *  The arguments \a num and \a name are for debugging purposes only.
     *  There is a convenience function Config_getString() for this.
     */
    std::string &getString(const std::string &name, const std::string &fileName = "",int num = -1) const;

    /*! Returns the value of the list option with name \a fileName. 
     *  The arguments \a num and \a name are for debugging purposes only.
     *  There is a convenience function Config_getList() for this.
     */
    std::vector<std::string> &getList(const std::string &name, const std::string &fileName = "",int num = -1) const;

    /*! Returns the value of the enum option with name \a fileName. 
     *  The arguments \a num and \a name are for debugging purposes only.
     *  There is a convenience function Config_getEnum() for this.
     */
    std::string  &getEnum(const std::string &name, const std::string &fileName = "",int num = -1) const;

    /*! Returns the value of the integer option with name \a fileName. 
     *  The arguments \a num and \a name are for debugging purposes only.
     *  There is a convenience function Config_getInt() for this.
     */
    int      &getInt(const std::string &name, const std::string &fileName = "",int num = -1) const;

    /*! Returns the value of the boolean option with name \a fileName. 
     *  The arguments \a num and \a name are for debugging purposes only.
     *  There is a convenience function Config_getBool() for this.
     */
    bool     &getBool(const std::string &name, const std::string &fileName = "",int num = -1) const;

    /*! Returns the ConfigOption corresponding with \a name or 0 if
     *  the option is not supported.
     */
    ConfigOptionAbstract *get(const std::string &name) const
    {
      return m_dict->find(name); 
    }
    /* @} */

    /*! 
     *  @name Adding configuration options. 
     *  @{
     */

    /*! Starts a new configuration section with \a name and description \a doc.
     *  \returns An object representing the option.
     */
    ConfigInfo   *addInfo(const std::string &name,const std::string &doc)
    {
      ConfigInfo *result = new ConfigInfo(name,doc);
      m_options->append(result);
      return result;
    }

    /*! Adds a new string option with \a name and documentation \a doc.
     *  \returns An object representing the option.
     */
    ConfigString *addString(const std::string &name,
                            const std::string &doc)
    {
      ConfigString *result = new ConfigString(name,doc);
      m_options->append(result);
      m_dict->insert(name,result);
      return result;
    }

    /*! Adds a new enumeration option with \a name and documentation \a doc
     *  and initial value \a defVal. 
     *  \returns An object representing the option.
     */
    ConfigEnum   *addEnum(const std::string &name,
                          const std::string &doc,
                          const std::string &defVal)
    {
      ConfigEnum *result = new ConfigEnum(name,doc,defVal);
      m_options->append(result);
      m_dict->insert(name,result);
      return result;
    }

    /*! Adds a new string option with \a name and documentation \a doc.
     *  \returns An object representing the option.
     */
    ConfigList   *addList(const std::string &name,
                          const std::string &doc)
    {
      ConfigList *result = new ConfigList(name,doc);
      m_options->append(result);
      m_dict->insert(name,result);
      return result;
    }

    /*! Adds a new integer option with \a name and documentation \a doc.
     *  The integer has a range between \a minVal and \a maxVal and a
     *  default value of \a defVal.
     *  \returns An object representing the option.
     */
    ConfigInt    *addInt(const std::string &name,
                         const std::string &doc,
                         int minVal,int maxVal,int defVal)
    {
      ConfigInt *result = new ConfigInt(name,doc,minVal,maxVal,defVal);
      m_options->append(result);
      m_dict->insert(name,result);
      return result;
    }

    /*! Adds a new boolean option with \a name and documentation \a doc.
     *  The boolean has a default value of \a defVal.
     *  \returns An object representing the option.
     */
    ConfigBool   *addBool(const std::string &name,
                          const std::string &doc,
                          bool defVal)
    {
      ConfigBool *result = new ConfigBool(name,doc,defVal);
      m_options->append(result);
      m_dict->insert(name,result);
      return result;
    }
    /*! Adds an option that has become obsolete. */
    ConfigOptionAbstract *addObsolete(const std::string &name)
    {
      ConfigObsolete *option = new ConfigObsolete(name);
      m_dict->insert(name,option);
      m_obsolete->append(option);
      return option;
    }
    /*! Adds an option that has been disabled at compile time. */
    ConfigOptionAbstract *addDisabled(const std::string &name)
    {
      ConfigDisabled *option = new ConfigDisabled(name);
      m_dict->insert(name,option);
      m_disabled->append(option);
      return option;
    }
    /*! @} */

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

  protected:

    Config()
    { 
    	addConfigOptions(*this);
    }
   ~Config()
    {
    }
   static std::string convertToComment(const std::string &s, const std::string &u);
   static void Config::addConfigOptions(Config &cfg);
  private:
    void checkFileName(const std::string &);
    std::vector<ConfigOption> m_options;
    std::vector<ConfigOption> m_obsolete;
    std::vector<ConfigOption> m_disabled;
    std::vector<ConfigOption> m_dict;
    static std::unique_ptr<Config> m_instance = std::make_unique<Config>();
    std::string m_startComment;
    std::string m_userComment;
    std::string m_header;
};

}
#endif
