/******************************************************************************
 *
 * Copyright (C) 1997-2015 by Dimitri van Heesch.
 * Copyright (C) 2016		  Klemens D. Morgenstern
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

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <list>
#include <string>
#include <memory>
#include <cereal/types/string.hpp>

namespace DoxyFrame
{

class StorageIntf;

/*! \brief This class contains the information about the argument of a
 *         function or template
 *
 */
struct Argument
{

  bool hasDocumentation() const
  {
    return !name.empty() && !docs.empty();
  }

  std::string attrib;   /*!< Argument's attribute (IDL only) */
  std::string type;     /*!< Argument's type */
  std::string canType;  /*!< Cached value of canonical type (after type resolution). Empty initially. */
  std::string name;     /*!< Argument's name (may be empty) */
  std::string array;    /*!< Argument's array specifier (may be empty) */
  std::string defval;   /*!< Argument's default value (may be empty) */
  std::string docs;     /*!< Argument's documentation (may be empty) */
  std::string typeConstraint;  /*!< Used for Java generics: \<T extends C\> */

  template<typename Archive>
  void serialize(Archive & a)
  {
	  a & CEREAL_NVP(attrib);
	  a & CEREAL_NVP(type);
	  a & CEREAL_NVP(canType);
	  a & CEREAL_NVP(name);
	  a & CEREAL_NVP(array);
	  a & CEREAL_NVP(defval);
	  a & CEREAL_NVP(docs);
	  a & CEREAL_NVP(typeConstraint);
  }

};

/*! \brief This class represents an function or template argument list. 
 *
 *  This class also stores some information about member that is typically
 *  put after the argument list, such as whether the member is const, 
 *  volatile or pure virtual.
 */
struct ArgumentList : public std::list<Argument>
{


    /*! Does any argument of this list have documentation? */
    bool hasDocumentation() const
    {
   	  for (auto & a : *this)
   		  if (a.hasDocumentation())
   			  return true;
    	  return false;
    }
    /*! Does the member modify the state of the class? default: FALSE. */
    bool constSpecifier = false;
    /*! Is the member volatile? default: FALSE. */
    bool volatileSpecifier = false;
    /*! Is this a pure virtual member? default: FALSE */
    bool pureSpecifier = false;
    /*! C++11 style Trailing return type? */
    std::string trailingReturnType;
    /*! method with =delete */
    bool isDeleted = false;

    template<typename Archive>
    void serialize(Archive & a)
    {
  	  a & CEREAL_NVP(constSpecifier);
  	  a & CEREAL_NVP(volatileSpecifier);
  	  a & CEREAL_NVP(pureSpecifier);
  	  a & CEREAL_NVP(trailingReturnType);
  	  a & CEREAL_NVP(isDeleted);

    }

};

}
#endif
