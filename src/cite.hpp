/******************************************************************************
 *
 * 
 *
 * Copyright (C) 2011 by Dimitri van Heesch
 * Copyright (C) 2016 by Klemens D. Morgenstern
 * Based on a patch by David Munger
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

#ifndef CITEDB_H
#define CITEDB_H

#include <unordered_set>
#include <boost/optional.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_set.hpp>

namespace DoxyFrame
{

/// String constants for citations
struct CiteConsts
{
  static const std::string fileName;
  static const std::string anchorPrefix;

};

/// Citation-related data.
struct CiteInfo
{
   CiteInfo(const std::string & t_label,
		    const std::string &t_text = std::string(),
			const  std::string &t_fullText = std::string(),
	        const std::string &t_ref = QString() )
	      	  	 : label(t_label), text(t_text), fullText(t_fullText), ref(t_ref) {
	   }

   CiteInfo(const CiteInfo&) = default;
   CiteInfo(CiteInfo&&) = default;

   CiteInfo(const CiteInfo&) = default;
   CiteInfo(CiteInfo&&) = default;


  std::string label;
  std::string text;
  std::string fullText;
  std::string ref;

  template<typename Archive>
  void serialize(Archive &a)
  {
	  a & CEREAL_NVP(label);
	  a & CEREAL_NVP(text);
	  a & CEREAL_NVP(fullText);
	  a & CEREAL_NVP(ref);
  }
};


inline bool operator==(const CiteInfo& lhs, const CiteInfo& rhs) { return lhs.label == rhs.label; };
inline bool operator!=(const CiteInfo& lhs, const CiteInfo& rhs) { return lhs.label != rhs.label; };

}

namespace std
{
    template<> struct hash<DoxyFrame::CiteInfo>
    {
        typedef DoxyFrame::CiteInfo argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const
        {
            return std::hash<std::string>()(s.label);
        }
    };

}

namespace DoxyFrame
{

/**
 * @brief Cite database access class.
 * @details This class provides access do the database of bibliographic 
 * references through the bibtex backend.
 */
struct CiteDict
{
    /** Insert a citation identified by \a label into the database */
    void insert(const std::string& label) {	m_entries.insert(label); }
    /** Emplace a citation from a string */
    void emplace(const std::string& label){	m_entries.emplace(label);}
    /** Return the citation info for a given \a label */
    CiteInfo * const find(const std::string& label) const
    {
    	auto itr = m_entries.find(label);
    	return (m_entries.end() == itr) ? nullptr : &*itr ;
    }

    /** Generate the citations page */
    void generatePage() const;

    /** clears the database */
    void clear() 		{ return m_entries.clear(); }

    /** return TRUE if there are no citations. 
     *  Only valid after calling resolve() 
     */
    bool empty() const 	{ return m_entries.empty();}

    /** writes the latex code for the standard bibliography 
     *  section to text stream \a t 
     */
    void writeLatexBibliography(FTextStream &t);

    template<typename Archive>
    void serialize(Archive &a)
    {
    	a & CEREAL_NVP(m_entries);
    	a & CEREAL_NVP(m_baseFileName);
    }

  private:
    std::unordered_set<std::string, CiteInfo> m_entries;
    std::string m_baseFileName;
};

}
#endif
