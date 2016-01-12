/******************************************************************************
 *
 * 
 *
 * Copyright (C) 1997-2015 by Dimitri van Heesch.
 * Copyright (C) 2016		  Klemens D. Morgenstern
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

#ifndef DEFINE_H
#define DEFINE_H

#include <config.hpp>
#include <list>
#include <string>
#include <unordered_map>
#include <memory>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/unordered_map.hpp>

namespace DoxyFrame
{


class FileDef;

/** A class representing a macro definition. */
struct Define
{
    bool hasDocumentation() {return definition && (doc || Config_getBool("EXTRACT_ALL"));}

    std::string name;
    std::string definition;
    std::string fileName;
    std::string doc;
    std::string brief;
    std::string args;
    std::string anchor;
    std::shared_ptr<FileDef> fileDef;
    int lineNr 		= 1;
    int columnNr 	= 1;
    int nargs 		= -1;
    bool undef		= false;
    bool varArgs	= false;
    bool isPredefined = false;
    bool nonRecursive = false;
    template<typename Archive>
    void serialize(Archive & a)
    {
        a & CEREAL_NVP(name);
        a & CEREAL_NVP(definition);
        a & CEREAL_NVP(fileName);
        a & CEREAL_NVP(doc);
        a & CEREAL_NVP(brief);
        a & CEREAL_NVP(args);
        a & CEREAL_NVP(anchor);
        a & CEREAL_NVP(fileDef);
        a & CEREAL_NVP(lineNr);
        a & CEREAL_NVP(columnNr);
        a & CEREAL_NVP(nargs);
        a & CEREAL_NVP(undef);
        a & CEREAL_NVP(varArgs);
        a & CEREAL_NVP(isPredefined);
        a & CEREAL_NVP(nonRecursive);
    }
    int compare(const Define &d1) const
    {
        return name.compare(d1.name);
    }
};

/** A list of Define objects. */
struct DefineList : std::list<Define> {};


/** A list of Define objects associated with a specific name. */
struct DefineName : public std::list<Define>
{
    DefineName(const std::string &n) : name(n) {}

    std::string name;
};

/** A list of DefineName objects. */
class DefineNameList : public std::list<Define>
{
};

/** An unsorted dictionary of Define objects. */
typedef std::unordered_map<std::string, Define> DefineDict;

/** A sorted dictionary of DefineName object. */
typedef std::unordered_map<std::string, DefineName> DefineNameDict;

}
#endif
