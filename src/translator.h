/*************************************************************************
 * Copyright (C) 2015 Klemens D. Morgenstern
 * Copyright (C) 2014-2015 Barbara Geller & Ansel Sermersheim
 * Copyright (C) 1997-2014 by Dimitri van Heesch.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License version 2
 * is hereby granted. No representations are made about the suitability of
 * this software for any purpose. It is provided "as is" without express or
 * implied warranty. See the GNU General Public License for more details.
 *
 * Documents produced by DoxyPress are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
*************************************************************************/

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <boost/locale.hpp>
#include <boost/format.hpp>

class Translator
{
 public:

   /*! Used to get the LaTeX command(s) for the language support.
    *  This method should return a string with commands that switch LaTeX to the desired language.
    *
    *  <pre>"\\usepackage[german]{babel}\n"
    *  </pre>
    *
    *  <pre>"\\usepackage{polski}\n"
    *  "\\usepackage[latin2]{inputenc}\n"
    *  "\\usepackage[T1]{fontenc}\n"
    *  </pre>
    *
    * The English LaTeX does not use such commands.  Because of this
    * the empty string is returned in this implementation.
    */
   std::string latexLanguageSupportCommand() {
      return boost::locale::translate("latexSupport", "remove-value").str();
   }

   /*! used in the compound documentation before a list of related functions. */
   std::string RelatedFunctions() {
      return boost::locale::translate("doxy-text", "Related Functions");
   }

   /*! subscript for the related functions. */
   std::string RelatedSubscript() {
      return boost::locale::translate("doxy-text", "These are not member functions");
   }

   /*! header that is put before the detailed description of files, classes and namespaces. */
   std::string DetailedDescription() {
      return boost::locale::translate("doxy-text", "Detailed Description");
   }

   /*! header that is put before the list of typedefs. */
   std::string MemberTypedefDocumentation() {
      return boost::locale::translate("doxy-text", "Member Typedef Documentation");
   }

   /*! header that is put before the list of enumerations. */
   std::string MemberEnumerationDocumentation() {
      return boost::locale::translate("doxy-text", "Member Enumeration Documentation");
   }

   /*! header that is put before the list of member functions. */
   std::string MemberFunctionDocumentation() {
      return boost::locale::translate("doxy-text", "Member Function Documentation");
   }

   /*! header that is put before the list of member attributes. */
   std::string MemberDataDocumentation(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Field Documentation");
      } else {
         return boost::locale::translate("doxy-text", "Member Data Documentation");
      }
   }

   /*! this is the text of a link put after brief descriptions. */
   std::string More() {
      return boost::locale::translate("doxy-text", "More...");;
   }

   /*! put in the class documentation */
   std::string ListOfAllMembers() {
      return boost::locale::translate("doxy-text", "List of all members");
   }

   /*! used as the title of the "list of all members" page of a class */
   std::string MemberList() {
      return boost::locale::translate("doxy-text", "Member List");
   }

   /*! this is the first part of a sentence that is followed by a class name */
   std::string ThisIsTheListOfAllMembers() {
      return boost::locale::translate("doxy-text", "This is the complete list of members for ");
   }

   /*! this is the remainder of the sentence after the class name */
   std::string IncludingInheritedMembers() {
      return boost::locale::translate("doxy-text", ", including all inherited members.");
   }

   /*! this is put at the author sections at the bottom of man pages.
    *  parameter s is name of the project name.
    */
   std::string GeneratedAutomatically(const std::string &s) {
      if (! s.empty() ) {
         return boost::locale::translate("doxy-text", "Generated automatically by DoxyPress for %1% from the source code.")% (s);

      } else {
         return boost::locale::translate("doxy-text", "Generated automatically by DoxyPress from the source code.");

      }
   }

   /*! put after an enum name in the list of all members */
   std::string EnumName() {
      return boost::locale::translate("doxy-text", "enum name");;
   }

   /*! put after an enum value in the list of all members */
   std::string EnumValue() {
      return boost::locale::translate("doxy-text", "enum value");
   }

   /*! put after an undocumented member in the list of all members */
   std::string DefinedIn() {
      return boost::locale::translate("doxy-text", "defined in");
   }

   /*! This is put above each page as a link to the list of all groups of
    *  compounds or files (see the \\group command).
    */
   std::string Modules() {
      return boost::locale::translate("doxy-text", "Modules");;
   }

   /*! This is put above each page as a link to the class hierarchy */
   std::string ClassHierarchy() {
      return boost::locale::translate("doxy-text", "Class Hierarchy");
   }

   /*! This is put above each page as a link to the list of annotated classes */
   std::string CompoundList(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Structures");
      } else {
         return boost::locale::translate("doxy-text", "Class List");
      }
   }

   /*! This is put above each page as a link to the list of documented files */
   std::string FileList() {
      return boost::locale::translate("doxy-text", "File List");
   }

   /*! This is put above each page as a link to all members of compounds. */
   std::string CompoundMembers(bool optimize_c = false) {
	  if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Fields");
      } else {
         return boost::locale::translate("doxy-text", "Class Members");
      }
   }

   /*! This is put above each page as a link to all members of files. */
   std::string FileMembers(bool optimize_c = false) {
	  if (optimize_c) {
         return boost::locale::translate("doxy-text", "Globals");
      } else {
         return boost::locale::translate("doxy-text", "File Members");
      }
   }

   /*! This is put above each page as a link to all related pages. */
   std::string RelatedPages() {
      return boost::locale::translate("doxy-text", "Related Pages");
   }

   /*! This is put above each page as a link to all examples. */
   std::string Examples() {
      return boost::locale::translate("doxy-text", "Examples");
   }

   /*! This is put above each page as a link to the search engine. */
   std::string Search() {
      return boost::locale::translate("doxy-text", "Search");
   }

   /*! This is an introduction to the class hierarchy. */
   std::string ClassHierarchyDescription() {
      return boost::locale::translate("doxy-text", "This inheritance list is sorted roughly, "
                "but not completely, alphabetically:");
   }

   /*! This is an introduction to the list with all files. */
   std::string FileListDescription(bool extractAll) {
      if (extractAll) {
         return boost::locale::translate("doxy-text", "Here is a list of all files with brief "
                  "descriptions:");
      } else {
         return boost::locale::translate("doxy-text", "Here is a list of all documented files "
                  "with brief descriptions:");
      }
   }

   /*! This is an introduction to the annotated compound list. */
   std::string CompoundListDescription(bool optimize_c = false) {

	   if (optimize_c) {
         return boost::locale::translate("doxy-text",
               "Here are the data structures with brief descriptions:");

      } else {
         return boost::locale::translate("doxy-text", "Here are the classes, structs, "
                "unions and interfaces with brief descriptions:");
      }
   }

   /*! This is an introduction to the page with all class members. */
   std::string CompoundMembersDescription(bool extractAll, bool optimize_c = false) {
      std::string result;

      if (extractAll) {

         if (optimize_c) {
            result = boost::locale::translate("doxy-text", "Here is a list of all struct and union "
                  "fields with links to the structures/unions they belong to:");
         } else {
            result = boost::locale::translate("doxy-text", "Here is a list of all class members "
                  "with links to the classes they belong to:");
         }

      } else {

         if (optimize_c) {
            result = boost::locale::translate("doxy-text", "Here is a list of all documented struct "
                  "and union fields with links to the struct/union documentation for each field:");

         } else {
            result = boost::locale::translate("doxy-text", "Here is a list of all documented "
                  "class members with links to the class documentation for each member:");
         }

      }
      return result;
   }

   /*! This is an introduction to the page with all file members. */
   std::string FileMembersDescription(bool extractAll, bool optimize_c = false) {
      std::string result;

      if (extractAll) {

         if (optimize_c) {
            result = boost::locale::translate("doxy-text", "Here is a list of all functions, variables, "
                  "defines, enums, and typedefs with links to the files they belong to:");

         } else {
            result = boost::locale::translate("doxy-text", "Here is a list of all documented file members "
                  "with links to the files they belong to:");
         }

      } else  {

         if (optimize_c) {
            result = boost::locale::translate("doxy-text", "Here is a list of all functions, variables, defines, "
                   "enums, and typedefs with links to the documentation:");

         } else {
            result = boost::locale::translate("doxy-text", "Here is a list of all documented file members with "
                  "links to the documentation:");

         }
      }

      return result;
   }

   /*! This is an introduction to the page with the list of all examples */
   std::string ExamplesDescription() {
      return boost::locale::translate("doxy-text", "Here is a list of all examples:");
   }

   /*! This is an introduction to the page with the list of related pages */
   std::string RelatedPagesDescription() {
      return boost::locale::translate("doxy-text", "Here is a list of all related documentation pages:");
   }

   /*! This is an introduction to the page with the list of class/file groups */
   std::string ModulesDescription() {
      return boost::locale::translate("doxy-text", "Here is a list of all modules:");
   }

   // index titles (the project name is prepended for these)

   /*! This is used in HTML as the title of index.html. */
   std::string Documentation() {
      return boost::locale::translate("doxy-text", "Documentation");
   }

   /*! This is used in LaTeX as the title of the chapter with the
    * index of all groups.
    */
   std::string ModuleIndex() {
      return boost::locale::translate("doxy-text", "Module Index");
   }

   /*! This is used in LaTeX as the title of the chapter with the
    * class hierarchy.
    */
   std::string HierarchicalIndex() {
      return boost::locale::translate("doxy-text", "Hierarchical Index");
   }

   /*! This is used in LaTeX as the title of the chapter with the
    * annotated compound index.
    */
   std::string CompoundIndex(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Structure Index");
      } else {
         return boost::locale::translate("doxy-text", "Class Index");
      }
   }

   /*! This is used in LaTeX as the title of the chapter with the list of all files.
    */
   std::string FileIndex() {
      return boost::locale::translate("doxy-text", "File Index");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all groups.
    */
   std::string ModuleDocumentation() {
      return boost::locale::translate("doxy-text", "Module Documentation");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all classes, structs and unions.
    */
   std::string ClassDocumentation(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Structure Documentation");
      } else {
         return boost::locale::translate("doxy-text", "Class Documentation");
      }
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all files.
    */
   std::string FileDocumentation() {
      return boost::locale::translate("doxy-text", "File Documentation");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all examples.
    */
   std::string ExampleDocumentation() {
      return boost::locale::translate("doxy-text", "Example Documentation");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all related pages.
    */
   std::string PageDocumentation() {
      return boost::locale::translate("doxy-text", "Page Documentation");
   }

   /*! This is used in LaTeX as the title of the document */
   std::string ReferenceManual() {
      return boost::locale::translate("doxy-text", "Reference Manual");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of defines
    */
   std::string Defines() {
      return boost::locale::translate("doxy-text", "Macros");
   }

   std::string PublicTypedefs() {
      return boost::locale::translate("doxy-text", "Public Typedefs");
   }

   std::string ProtectedTypedefs() {
      return boost::locale::translate("doxy-text", "Protected Typedefs");
   }

   std::string PrivateTypedefs() {
      return boost::locale::translate("doxy-text", "Private Typedefs");
   }

   /*! This is used in the documentation of a file as a header before the list of typedefs
    */
   std::string Typedefs() {
      return boost::locale::translate("doxy-text", "Typedefs");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of enumerations
    */
   std::string Enumerations() {
      return boost::locale::translate("doxy-text", "Enums");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of (global) functions
    */
   std::string Functions() {
      return boost::locale::translate("doxy-text", "Functions");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of (global) variables
    */
   std::string Variables() {
      return boost::locale::translate("doxy-text", "Variables");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of (global) variables
    */
   std::string EnumerationValues() {
      return boost::locale::translate("doxy-text", "Enum Values");
   }

   /*! This is used in the documentation of a file before the list of
    *  documentation blocks for defines
    */
   std::string DefineDocumentation() {
      return boost::locale::translate("doxy-text", "Macro Definition Documentation");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for typedefs
    */
   std::string TypedefDocumentation() {
      return boost::locale::translate("doxy-text", "Typedef Documentation");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for enumeration types
    */
   std::string EnumerationTypeDocumentation() {
      return boost::locale::translate("doxy-text", "Enumeration Type Documentation");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for functions
    */
   std::string FunctionDocumentation() {
      return boost::locale::translate("doxy-text", "Function Documentation");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for variables
    */
   std::string VariableDocumentation() {
      return boost::locale::translate("doxy-text", "Variable Documentation");
   }

   /*! This is used in the documentation of a file/namespace/group before
    *  the list of links to documented compounds
    */
   std::string Compounds(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Structures");
      } else {
         return boost::locale::translate("doxy-text", "Classes");
      }
   }

   /*! This is used in the standard footer of each page and indicates when
    *  the page was generated
    */
   std::string GeneratedAt(const std::string &date, const std::string &projName) {

      if (projName.empty()) {
         return boost::format(boost::locale::translate("doxy-text", "Generated on %1% &nbsp; by")) % date;
      } else  {
         return boost::format(boost::locale::translate("doxy-text", "Generated on %1% for %2% &nbsp; by")) % date% projName;
      }
   }

   /*! this text is put before a class diagram */
   std::string ClassDiagram(const std::string &clName) {
      return boost::format(boost::locale::translate("doxy-text", "Inheritance diagram for %1%:")) % clName;
   }

   /*! this text is generated when the \\internal command is used. */
   std::string ForInternalUseOnly() {
      return boost::locale::translate("doxy-text", "For internal use only.");
   }

   /*! this text is generated when the \\warning command is used. */
   std::string Warning() {
      return boost::locale::translate("doxy-text", "Warning");
   }

   /*! this text is generated when the \\version command is used. */
   std::string Version() {
      return boost::locale::translate("doxy-text", "Version");
   }

   /*! this text is generated when the \\date command is used. */
   std::string Date() {
      return boost::locale::translate("doxy-text", "Date");
   }

   /*! this text is generated when the \\return command is used. */
   std::string Returns() {
      return boost::locale::translate("doxy-text", "Returns");
   }

   /*! this text is generated when the \\sa command is used. */
   std::string SeeAlso() {
      return boost::locale::translate("doxy-text", "See also");
   }

   /*! this text is generated when the \\param command is used. */
   std::string Parameters() {
      return boost::locale::translate("doxy-text", "Parameters");
   }

   /*! this text is generated when the \\exception command is used. */
   std::string Exceptions() {
      return boost::locale::translate("doxy-text", "Exceptions");
   }

   /*! this text is used in the title page of a LaTeX document. */
   std::string GeneratedBy() {
      return boost::locale::translate("doxy-text", "Generated by");
   }

   /*! used as the title of page containing all the index of all namespaces. */
   std::string NamespaceList() {
      return boost::locale::translate("doxy-text", "Namespace List");
   }

   /*! used as an introduction to the namespace list */
   std::string NamespaceListDescription(bool extractAll) {

      if (extractAll) {
         return boost::locale::translate("doxy-text", "Here is a list of all namespaces with "
                  "brief descriptions:");
      } else {
         return boost::locale::translate("doxy-text", "Here is a list of all documented namespaces "
                  "with brief descriptions:");
      }
   }

   /*! used in the class documentation as a header before the list of all
    *  friends of a class
    */
   std::string Friends() {
      return boost::locale::translate("doxy-text", "Friends");
   }

   /*! used in the class documentation as a header before the list of all
    * related classes
    */
   std::string RelatedFunctionDocumentation() {
      return boost::locale::translate("doxy-text", "Friends And Related Function Documentation");
   }

   /*! used as the title of the HTML page of a class/struct/union */
   std::string CompoundReference(const std::string &clName, ClassDef::CompoundType compType, bool isTemplate) {
      std::string result;

      switch (compType) {
         case ClassDef::Class:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Class Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Class Reference")) % (clName);
            }
            break;

         case ClassDef::Struct:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Struct Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Struct Reference")) % (clName);
            }
            break;

         case ClassDef::Union:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Union Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Union Reference")) % (clName);
            }
            break;

         case ClassDef::Interface:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Interface Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Interface Reference")) % (clName);
            }
            break;

         case ClassDef::Protocol:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Protocol Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Protocol Reference")) % (clName);
            }
            break;

         case ClassDef::Category:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Category Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Category Reference")) % (clName);
            }
            break;

         case ClassDef::Exception:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Exception Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Exception Reference")) % (clName);
            }
            break;

         default:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Reference")) % (clName);
            }
            break;
      }

      return result;
   }

   /*! used as the title of the HTML page of a file */
   std::string FileReference(const std::string &fileName) {
      return boost::format(boost::locale::translate("doxy-text", "%1% File Reference")) % (fileName);
   }

   /*! used as the title of the HTML page of a namespace */
   std::string NamespaceReference(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Namespace Reference"))% (name);
   }

   std::string PublicMembers() {
      return boost::locale::translate("doxy-text", "Public Member Functions");
   }

   std::string PublicSignals() {
      return boost::locale::translate("doxy-text", "Public Signals");
   }
   std::string ProtectedSignals() {
      return boost::locale::translate("doxy-text", "Protected Signals");
   }
   std::string PrivateSignals() {
      return boost::locale::translate("doxy-text", "Private Signals");
   }

   std::string StaticPublicMembers() {
      return boost::locale::translate("doxy-text", "Static Public Member Functions");
   }
   std::string ProtectedMembers() {
      return boost::locale::translate("doxy-text", "Protected Member Functions");
   }
   std::string PublicSlots() {
      return boost::locale::translate("doxy-text", "Public Slots");
   }
   std::string ProtectedSlots() {
      return boost::locale::translate("doxy-text", "Protected Slots");
   }
   std::string StaticProtectedMembers() {
      return boost::locale::translate("doxy-text", "Static Protected Member Functions");
   }
   std::string PrivateMembers() {
      return boost::locale::translate("doxy-text", "Private Member Functions");
   }
   std::string PrivateSlots() {
      return boost::locale::translate("doxy-text", "Private Slots");
   }
   std::string StaticPrivateMembers() {
      return boost::locale::translate("doxy-text", "Static Private Member Functions");
   }

   /*! this function is used to produce a comma-separated list of items.
    *  use generateMarker(i) to indicate where item i should be put.
    */
   std::string WriteList(int numEntries) {
      std::string result;

      // the inherits list contains `numEntries' classes
      for (int i = 0; i < numEntries; i++) {

         // generate placeholders for the class links, entry i in the list
         result += boost::format("@%1%") % i ;

         // order is left to right, @0, @1, @2, and @3

         if (i != numEntries - 1) {
            // not at the last entry, add separator

            if (i < numEntries - 2) {     // in the middle of the list
               result += ", ";

            } else {                      // at the second to last entry
               result += boost::locale::translate("doxy-text", ", and ");
            }
         }
      }

      return result;
   }

   /*! used in class documentation to produce a list of base classes,
    *  if class diagrams are disabled.
    */
   std::string InheritsList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Inherits %1%.")) % WriteList(numEntries);
   }

   /*! used in class documentation to produce a list of super classes,
    *  if class diagrams are disabled.
    */
   std::string InheritedByList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Inherited by %1%.")) % WriteList(numEntries);
   }

   /*! used in member documentation blocks to produce a list of
    *  members that are hidden by this one.
    */
   std::string ReimplementedFromList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Reimplemented from %1%.")) % WriteList(numEntries);
   }

   /*! used in member documentation blocks to produce a list of
    *  all member that overwrite the implementation of this member.
    */
   std::string ReimplementedInList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Reimplemented in %1%.")) % WriteList(numEntries);
   }

   /*! This is put above each page as a link to all members of namespaces. */
   std::string NamespaceMembers() {
      return boost::locale::translate("doxy-text", "Namespace Members");
   }

   /*! This is an introduction to the page with all namespace members */
   std::string NamespaceMemberDescription(bool extractAll) {
      if (extractAll) {
         return boost::locale::translate("doxy-text", "Here is a list of all namespace members with links "
                  "to the namespace documentation for each member:");
      } else {
         return boost::locale::translate("doxy-text", "Here is a list of all documented namespace members "
                  "with links to the namespaces they belong to:");
      }
   }

   /*! This is used in LaTeX as the title of the chapter with the
    *  index of all namespaces.
    */
   std::string NamespaceIndex() {
      return boost::locale::translate("doxy-text", "Namespace Index");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all namespaces.
    */
   std::string NamespaceDocumentation() {
      return boost::locale::translate("doxy-text", "Namespace Documentation");
   }

   /*! This is used in the documentation before the list of all
    *  namespaces in a file.
    */
   std::string Namespaces() {
      return boost::locale::translate("doxy-text", "Namespaces");
   }

   /*! This is put at the bottom of a class documentation page and is
    *  followed by a list of files that were used to generate the page.
    */
   std::string GeneratedFromFiles(ClassDef::CompoundType compType, bool single) {
      std::string result;

      switch (compType) {

         case ClassDef::Class:
            if (single) {
              result = boost::locale::translate("doxy-text", "The documentation for this class "
                     " was generated from the following file:");
            } else {
              result = boost::locale::translate("doxy-text", "The documentation for this class "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Struct:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this struct "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this struct "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Union:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this union "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this union "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Interface:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this interface "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this interface "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Protocol:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this protocol "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this protocol "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Category:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this category "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this category "
                     " was generated from the following files:");
            }
            break;

         case ClassDef::Exception:

            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this exception"
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this exception"
                     " was generated from the following files:");
            }
            break;

         default:

            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this "
                     " was generated from the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this "
                     " was generated from the following files:");
            }

            break;
      }

      return result;
   }

   /*! This is used as the heading text for the retval command. */
   std::string ReturnValues() {
      return boost::locale::translate("doxy-text", "Return Values");
   }

   /*! This is in the (quick) index as a link to the main page (index.html)
    */
   std::string MainPage() {
      return boost::locale::translate("doxy-text", "Main Page");
   }

   /*! This is used in references to page that are put in the LaTeX
    *  documentation. It should be an abbreviation of the word page.
    */
   std::string PageAbbreviation() {
      return boost::locale::translate("doxy-text", "p,");
   }

   std::string DefinedAtLineInSourceFile() {
      return boost::locale::translate("doxy-text", "Definition at line @0 of file @1.");
   }

   std::string DefinedInSourceFile() {
      return boost::locale::translate("doxy-text", "Definition in file @0.");
   }

   std::string Deprecated() {
      return boost::locale::translate("doxy-text", "Deprecated");
   }

   /*! this text is put before a collaboration diagram */
   std::string CollaborationDiagram(const std::string &clName) {
      return boost::format(boost::locale::translate("doxy-text", "Collaboration diagram for %1%:")) % (clName);
   }

   /*! this text is put before an include dependency graph */
   std::string InclDepGraph(const std::string &fName) {
      return boost::format(boost::locale::translate("doxy-text", "Include dependency graph for %1%:")) % (fName);
   }

   /*! header that is put before the list of constructor/destructors. */
   std::string ConstructorDocumentation() {
      return boost::locale::translate("doxy-text", "Constructor & Destructor Documentation");
   }

   /*! Used in the file documentation to point to the corresponding sources. */
   std::string GotoSourceCode() {
      return boost::locale::translate("doxy-text", "Go to the source code of this file.");
   }

   /*! Used in the file sources to point to the corresponding documentation. */
   std::string GotoDocumentation() {
      return boost::locale::translate("doxy-text", "Go to the documentation of this file.");
   }

   /*! Text for the \\pre command */
   std::string Precondition() {
      return boost::locale::translate("doxy-text", "Precondition");
   }

   /*! Text for the \\post command */
   std::string Postcondition() {
      return boost::locale::translate("doxy-text", "Postcondition");
   }
   /*! Text for the \\invariant command */
   std::string Invariant() {
      return boost::locale::translate("doxy-text", "Invariant");
   }

   /*! Text shown before a multi-line variable/enum initialization */
   std::string InitialValue() {
      return boost::locale::translate("doxy-text", "Initial value:");
   }
   /*! Text used the source code in the file index */
   std::string Code() {
      return boost::locale::translate("doxy-text", "code");
   }

   std::string GraphicalHierarchy() {
      return boost::locale::translate("doxy-text", "Graphical Class Hierarchy");
   }

   std::string GotoGraphicalHierarchy() {
      return boost::locale::translate("doxy-text", "Go to the graphical class hierarchy");
   }

   std::string GotoTextualHierarchy() {
      return boost::locale::translate("doxy-text", "Go to the textual class hierarchy");
   }

   std::string PageIndex() {
      return boost::locale::translate("doxy-text", "Page Index");
   }

   std::string Note() {
      return boost::locale::translate("doxy-text", "Note");
   }
   std::string PublicTypes() {
      return boost::locale::translate("doxy-text", "Public Types");
   }

   std::string PublicAttribs(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Fields");
      } else {
         return boost::locale::translate("doxy-text", "Public Attributes");
      }
   }

   std::string StaticPublicAttribs() {
      return boost::locale::translate("doxy-text", "Static Public Attributes");
   }

   std::string ProtectedTypes() {
      return boost::locale::translate("doxy-text", "Protected Types");
   }

   std::string ProtectedAttribs() {
      return boost::locale::translate("doxy-text", "Protected Attributes");
   }

   std::string StaticProtectedAttribs() {
      return boost::locale::translate("doxy-text", "Static Protected Attributes");
   }

   std::string PrivateTypes() {
      return boost::locale::translate("doxy-text", "Private Types");
   }

   std::string PrivateAttribs() {
      return boost::locale::translate("doxy-text", "Private Attributes");
   }

   std::string StaticPrivateAttribs() {
      return boost::locale::translate("doxy-text", "Static Private Attributes");
   }

   /*! Used as a marker that is put before a \\todo item */
   std::string Todo() {
      return boost::locale::translate("doxy-text", "Todo");
   }

   /*! Used as the header of the todo list */
   std::string TodoList() {
      return boost::locale::translate("doxy-text", "Todo List");
   }

   std::string ReferencedBy() {
      return boost::locale::translate("doxy-text", "Referenced by");
   }

   std::string Remarks() {
      return boost::locale::translate("doxy-text", "Remarks");
   }

   std::string Attention() {
      return boost::locale::translate("doxy-text", "Attention");
   }

   std::string InclByDepGraph() {
      return boost::locale::translate("doxy-text", "This graph shows which files "
                  "directly or indirectly include this file");
   }

   std::string Since() {
      return boost::locale::translate("doxy-text", "Since");
   }

   /*! title of the graph legend page */
   std::string LegendTitle() {
      return boost::locale::translate("doxy-text", "Graph Legend");
   }

   /*! page explaining how the dot graph's should be interpreted
    *  The %A in the text below are to prevent link to classes called "A".
    */
   std::string LegendDocs(const std::string &dotFormat) {

      return boost::format(boost::locale::translate("doxy-text",
         "This page explains how to interpret the graphs which are generated by DoxyPress.\n\n"
         "Consider the following example:\n"
         "\\code\n"
         "/*! Invisible class because of uncation */\n"
         "class Invisible { };\n\n"
         "/*! uncated class, inheritance relation is hidden */\n"
         "class uncated : public Invisible { };\n\n"
         "/* Class not documented with DoxyPress comments */\n"
         "class Undocumented { };\n\n"
         "/*! Class that is inherited using public inheritance */\n"
         "class PublicBase : public uncated { };\n\n"
         "/*! A template class */\n"
         "template<class T> class Templ { };\n\n"
         "/*! Class that is inherited using protected inheritance */\n"
         "class ProtectedBase { };\n\n"
         "/*! Class that is inherited using private inheritance */\n"
         "class PrivateBase { };\n\n"
         "/*! Class that is used by the Inherited class */\n"
         "class Used { };\n\n"
         "/*! Super class that inherits a number of other classes */\n"
         "class Inherited : public PublicBase,\n"
         "                  protected ProtectedBase,\n"
         "                  private PrivateBase,\n"
         "                  public Undocumented,\n"
         "                  public Templ<int>\n"
         "{\n"
         "  private:\n"
         "    Used *m_usedClass;\n"
         "};\n"
         "\\endcode\n"
         "This will result in the following graph:"
         "\n\n"
         "<center><img alt=\"\" src=\"graph_legend.%1%\"></center>\n"
         "\n"
         "The boxes in the above graph have the following meaning:\n\n"
         "<ul>\n"
         "<li>%A filled gray box represents the struct or class for which the "
         "graph is generated.</li>\n"
         "<li>%A box with a black border denotes a documented struct or class.</li>\n"
         "<li>%A box with a grey border denotes an undocumented struct or class.</li>\n"
         "<li>%A box with a red border denotes a documented struct or class for "
         "which not all inheritance/containment relations are shown. %A graph is "
         "truncated if it does not fit within the specified boundaries.</li>\n"
         "</ul>\n"
         "\n"
         "The arrows have the following meaning:\n"
         "\n"
         "<ul>\n"
         "<li>%A dark blue arrow is used to visualize a public inheritance "
         "relation between two classes.</li>\n"
         "<li>%A dark green arrow is used for protected inheritance.</li>\n"
         "<li>%A dark red arrow is used for private inheritance.</li>\n"
         "<li>%A purple dashed arrow is used if a class is contained or used "
         "by another class. The arrow is labeled with the variable(s) "
         "through which the pointed class or struct is accessible.</li>\n"
         "<li>%A yellow dashed arrow denotes a relation between a template instance and "
         "the template class it was instantiated from. The arrow is labeled with "
         "the template parameters of the instance.</li>\n"
         "</ul>\n") ) % (dotFormat);
   }

   /*! text for the link to the legend page */
   std::string Legend() {
      return boost::locale::translate("doxy-text", "legend");
   }

   /*! Used as a marker that is put before a test item */
   std::string Test() {
      return boost::locale::translate("doxy-text", "Test");
   }

   /*! Used as the header of the test list */
   std::string TestList() {
      return boost::locale::translate("doxy-text", "Test List");
   }

   /*! Used as a section header for IDL properties */
   std::string Properties() {
      return boost::locale::translate("doxy-text", "Properties");
   }

   /*! Used as a section header for IDL property documentation */
   std::string PropertyDocumentation() {
      return boost::locale::translate("doxy-text", "Property Documentation");
   }

   /*! Used for Java classes in the summary section of Java packages */
   std::string Classes(bool optimize_c = false) {
      if (optimize_c) {
         return boost::locale::translate("doxy-text", "Data Structures");
      } else {
         return boost::locale::translate("doxy-text", "Classes");
      }
   }

   /*! Used as the title of a Java package */
   std::string Package(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "Package %1%")) % (name);
   }

   /*! Title of the package index page */
   std::string PackageList() {
      return boost::locale::translate("doxy-text", "Package List");
   }

   /*! The description of the package index page */
   std::string PackageListDescription() {
      return boost::locale::translate("doxy-text", "Here are the packages with "
                  "brief descriptions (if available):");
   }

   /*! The link name in the Quick links header for each page */
   std::string Packages() {
      return boost::locale::translate("doxy-text", "Packages");
   }

   /*! Text shown before a multi-line define */
   std::string DefineValue() {
      return boost::locale::translate("doxy-text", "Value:");
   }

   /*! Used as a marker that is put before a \\bug item */
   std::string Bug() {
      return boost::locale::translate("doxy-text", "Bug");
   }

   /*! Used as the header of the bug list */
   std::string BugList() {
      return boost::locale::translate("doxy-text", "Bug List");
   }

   /*! Used as ansi cpg for RTF file
    *
    * The following table shows the correlation of Charset name, Charset Value and
    * <pre>
    * Codepage number:
    * Charset Name       Charset Value(hex)  Codepage number
    * ------------------------------------------------------
    * DEFAULT_CHARSET           1 (x01)
    * SYMBOL_CHARSET            2 (x02)
    * OEM_CHARSET             255 (xFF)
    * ANSI_CHARSET              0 (x00)            1252
    * RUSSIAN_CHARSET         204 (xCC)            1251
    * EE_CHARSET              238 (xEE)            1250
    * GREEK_CHARSET           161 (xA1)            1253
    * TURKISH_CHARSET         162 (xA2)            1254
    * BALTIC_CHARSET          186 (xBA)            1257
    * HEBREW_CHARSET          177 (xB1)            1255
    * ARABIC _CHARSET         178 (xB2)            1256
    * SHIFTJIS_CHARSET        128 (x80)             932
    * HANGEUL_CHARSET         129 (x81)             949
    * GB2313_CHARSET          134 (x86)             936
    * CHINESEBIG5_CHARSET     136 (x88)             950
    * </pre>
    *
    */
   std::string RTFansicp() {
      return boost::locale::translate("doxy-rtf|trRTFansicp", "1252");
   }

   /*! Used as ansicpg for RTF fcharset
    *  \see RTFansicp() for a table of possible values.
    */
   std::string RTFCharSet() {
      return boost::locale::translate("doxy-rtf|trRTFCharSet", "0");
   }

   /*! Used as header RTF general index */
   std::string RTFGeneralIndex() {
      return boost::locale::translate("doxy-text", "Index");
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names of the category.
    */
   std::string Class(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Class");
         } else  {
            return boost::locale::translate("doxy-text", "Classes");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "class");
         } else  {
            return boost::locale::translate("doxy-text", "classes");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string File(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "File");
         } else  {
            return boost::locale::translate("doxy-text", "Files");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "file");
         } else  {
            return boost::locale::translate("doxy-text", "files");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Namespace(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Namespace");
         } else  {
            return boost::locale::translate("doxy-text", "Namespaces");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "namespace");
         } else  {
            return boost::locale::translate("doxy-text", "namespaces");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names of the category.
    */
   std::string Group(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Module");
         } else  {
            return boost::locale::translate("doxy-text", "Modules");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "module");
         } else  {
            return boost::locale::translate("doxy-text", "modules");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names of the category.
    */
   std::string Page(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Page");
         } else  {
            return boost::locale::translate("doxy-text", "Pages");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "page");
         } else  {
            return boost::locale::translate("doxy-text", "pages");
         }
      }
   }


   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Member(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Member");
         } else  {
            return boost::locale::translate("doxy-text", "Members");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "member");
         } else  {
            return boost::locale::translate("doxy-text", "members");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Global(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Global");
         } else  {
            return boost::locale::translate("doxy-text", "Globals");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "global");
         } else {
            return boost::locale::translate("doxy-text", "globals");
         }
      }
   }

   /*! This text is generated when the \\author command is used and
    *  for the author section in man pages. */
   std::string Author(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Author");
         } else  {
            return boost::locale::translate("doxy-text", "Authors");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "author");
         } else  {
            return boost::locale::translate("doxy-text", "Authors");
         }
      }
   }

   /*! This text is put before the list of members referenced by a member
    */
   std::string References() {
      return boost::locale::translate("doxy-text", "References");
   }

   /*! used in member documentation blocks to produce a list of
    *  members that are implemented by this one.
    */
   std::string ImplementedFromList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Implements %1%." )) % WriteList(numEntries);
   }

   /*! used in member documentation blocks to produce a list of
    *  all members that implement this abstract member.
    */
   std::string ImplementedInList(int numEntries) {
      return boost::format(boost::locale::translate("doxy-text", "Implemented %1%.")) % WriteList(numEntries);
   }

   /*! used in RTF documentation as a heading for the Table
    *  of Contents.
    */
   std::string RTFTableOfContents() {
      return boost::locale::translate("doxy-text", "Table of Contents");
   }

   /*! Used as the header of the list of item that have been
    *  flagged deprecated
    */
   std::string DeprecatedList() {
      return boost::locale::translate("doxy-text", "Deprecated List");
   }

   /*! Used as a header for declaration section of the events found in
    * a C# program
    */
   std::string Events() {
      return boost::locale::translate("doxy-text", "Events");
   }

   /*! Header used for the documentation section of a class' events. */
   std::string EventDocumentation() {
      return boost::locale::translate("doxy-text", "Event Documentation");
   }

   /*! Used as a heading for a list of Java class types with package scope.
    */
   std::string PackageTypes() {
      return boost::locale::translate("doxy-text", "Package Types");
   }

   /*! Used as a heading for a list of Java class functions with package
    * scope.
    */
   std::string PackageMembers() {
      return boost::locale::translate("doxy-text", "Package Functions");
   }

   /*! Used as a heading for a list of static Java class functions with
    *  package scope.
    */
   std::string StaticPackageMembers() {
      return boost::locale::translate("doxy-text", "Static Package Functions");
   }

   /*! Used as a heading for a list of Java class variables with package
    * scope.
    */
   std::string PackageAttribs() {
      return boost::locale::translate("doxy-text", "Package Attributes");
   }

   /*! Used as a heading for a list of static Java class variables with
    * package scope.
    */
   std::string StaticPackageAttribs() {
      return boost::locale::translate("doxy-text", "Static Package Attributes");
   }

   /*! Used in the quick index of a class/file/namespace member list page
    *  to link to the unfiltered list of all members.
    */
   std::string All() {
      return boost::locale::translate("doxy-text", "All");
   }

   /*! Put in front of the call graph for a function. */
   std::string CallGraph() {
      return boost::locale::translate("doxy-text", "Here is the call graph for this function:");
   }

    /*! This string is used as the title for the page listing the search
    *  results.
    */
   std::string SearchResultsTitle() {
      return boost::locale::translate("doxy-text", "Search Results");
   }

   /*! This string is put just before listing the search results. The
    *  text can be different depending on the number of documents found.
    *  Inside the text you can put the special marker $num to insert
    *  the number representing the actual number of search results.
    *  The @a numDocuments parameter can be either 0, 1 or 2, where the
    *  value 2 represents 2 or more matches. HTML markup is allowed inside
    *  the returned string.
    */
   std::string SearchResults(int numDocuments) {
      if (numDocuments == 0) {
         return boost::locale::translate("doxy-text",  "Sorry, no documents matching your query.");

      } else if (numDocuments == 1) {
         return boost::locale::translate("doxy-text", "Found <b>1</b> document matching your query.");

      } else {
         return boost::locale::translate("doxy-text", "Found <b>$num</b> documents matching your query. "
                "Showing best matches first.");
      }
   }
   /*! This string is put before the list of matched words, for each search
    *  result. What follows is the list of words that matched the query.
    */
   std::string SearchMatches() {
      return boost::locale::translate("doxy-text", "Matches:");
   }

   /*! This is used in HTML as the title of page with source code for file filename
    */
   std::string SourceFile(const std::string &filename) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Source File")) % (filename);
   }

   /*! This is used as the name of the chapter containing the directory
    *  hierarchy.
    */
   std::string DirIndex() {
      return boost::locale::translate("doxy-text", "Directory Hierarchy");
   }

   /*! This is used as the name of the chapter containing the documentation
    *  of the directories.
    */
   std::string DirDocumentation() {
      return boost::locale::translate("doxy-text", "Directory Documentation");
   }

   /*! This is used as the title of the directory index and also in the
    *  Quick links of an HTML page, to link to the directory hierarchy.
    */
   std::string Directories() {
      return boost::locale::translate("doxy-text", "Directories");
   }

   /*! This returns a sentences that introduces the directory hierarchy.
    *  and the fact that it is sorted alphabetically per level
    */
   std::string DirDescription() {
      return boost::locale::translate("doxy-text", "This directory hierarchy is sorted roughly, "
             "but not completely, alphabetically:");
   }

   /*! This returns the title of a directory page. The name of the
    *  directory is passed via \a dirName.
    */
   std::string DirReference(const std::string &dirName) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Directory Reference")) % (dirName);
   }

   /*! This returns the word directory with or without starting capital
    *  (\a first_capital) and in sigular or plural form (\a singular).
    */
   std::string Dir(bool first_capital, bool singular) {
      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Directory");
         } else {
            return boost::locale::translate("doxy-text", "Directories");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "directory");
         } else {
            return boost::locale::translate("doxy-text", "directories");
         }
      }
   }

   /*! This text is added to the documentation when the \\overload command
    *  is used for a overloaded function.
    */
   std::string OverloadText() {
      return boost::locale::translate("doxy-text",  "This is an overloaded member function, "
             "provided for convenience. It differs from the above "
             "function only in what argument(s) it accepts.");
   }

   /*! This is used to introduce a caller (or called-by) graph */
   std::string CallerGraph() {
      return boost::locale::translate("doxy-text", "Here is the caller graph for this function:");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for enumeration values
    */
   std::string EnumerationValueDocumentation() {
      return boost::locale::translate("doxy-text", "Enumerator Documentation");
   }

   /*! header that is put before the list of member subprograms (Fortran). */
   std::string MemberFunctionDocumentationFortran() {
      return boost::locale::translate("doxy-text", "Member Function/Subroutine Documentation");
   }

   /*! This is put above each page as a link to the list of annotated data types (Fortran). */
   std::string CompoundListFortran() {
      return boost::locale::translate("doxy-text", "Data Types List");
   }

   /*! This is put above each page as a link to all members of compounds (Fortran). */
   std::string CompoundMembersFortran() {
      return boost::locale::translate("doxy-text", "Data Fields");
   }

   /*! This is an introduction to the annotated compound list (Fortran). */
   std::string CompoundListDescriptionFortran() {
      return boost::locale::translate("doxy-text", "Here are the data types with brief descriptions:");
   }

   /*! This is an introduction to the page with all data types (Fortran). */
   std::string CompoundMembersDescriptionFortran(bool extractAll) {
      std::string result;

      if (extractAll) {
         result = boost::locale::translate("doxy-text", "Here is a list of all data types "
                  "members with links to the data types they belong to:");
      } else {
         result = boost::locale::translate("doxy-text", "Here is a list of all documented "
                  "data types members with links to the data structure documentation for each member:");
      }
      return result;
   }

   /*! This is used in LaTeX as the title of the chapter with the
    * annotated compound index (Fortran).
    */
   std::string CompoundIndexFortran() {
      return boost::locale::translate("doxy-text", "Data Type Index");
   }

   /*! This is used in LaTeX as the title of the chapter containing
    *  the documentation of all data types (Fortran).
    */
   std::string TypeDocumentation() {
      return boost::locale::translate("doxy-text", "Data Type Documentation");
   }

   /*! This is used in the documentation of a file as a header before the
    *  list of (global) subprograms (Fortran).
    */
   std::string Subprograms() {
      return boost::locale::translate("doxy-text", "Functions/Subroutines");
   }

   /*! This is used in the documentation of a file/namespace before the list
    *  of documentation blocks for subprograms (Fortran)
    */
   std::string SubprogramDocumentation() {
      return boost::locale::translate("doxy-text", "Function/Subroutine Documentation");
   }

   /*! This is used in the documentation of a file/namespace/group before
    *  the list of links to documented compounds (Fortran)
    */
   std::string DataTypes() {
      return boost::locale::translate("doxy-text", "Data Types");
   }

   /*! used as the title of page containing all the index of all modules (Fortran). */
   std::string ModulesList() {
      return boost::locale::translate("doxy-text", "Modules List");
   }

   /*! used as an introduction to the modules list (Fortran) */
   std::string ModulesListDescription(bool extractAll) {
      if (extractAll) {
         return boost::locale::translate("doxy-text", "Here is a list of all modules with brief descriptions:");
      } else {
         return boost::locale::translate("doxy-text", "Here is a list of all documented modules with brief descriptions:");
      }
   }

   /*! used as the title of the HTML page of a module/type (Fortran) */
   std::string CompoundReferenceFortran(const std::string &clName, ClassDef::CompoundType compType,bool isTemplate) {
      std::string result;

      switch (compType) {
         case ClassDef::Class:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Module Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Module Reference")) % (clName);
            }
            break;

         case ClassDef::Struct:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Type Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Type Reference")) % (clName);
            }
            break;

         case ClassDef::Union:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Union Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Union Reference")) % (clName);
            }
            break;

         case ClassDef::Interface:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Interface Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Interface Reference")) % (clName);
            }
            break;

         case ClassDef::Protocol:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Protocol Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1%  Protocol Reference")) % (clName);
            }
            break;

         case ClassDef::Category:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Category Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Category Reference")) % (clName);
            }
            break;

         case ClassDef::Exception:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Exception Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Exception Reference")) % (clName);
            }
            break;

          default:
            if (isTemplate) {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Template Reference")) % (clName);
            } else {
               result = boost::format(boost::locale::translate("doxy-text", "%1% Reference")) % (clName);
            }
            break;
      }

      return result;
   }
   /*! used as the title of the HTML page of a module (Fortran) */
   std::string ModuleReference(const std::string &namespaceName) {
      return boost::locale::translate("doxy-text", "%1% Module Reference")% (namespaceName);
   }

   /*! This is put above each page as a link to all members of modules. (Fortran) */
   std::string ModulesMembers() {
      return boost::locale::translate("doxy-text", "Module Members");
   }

   /*! This is an introduction to the page with all modules members (Fortran) */
   std::string ModulesMemberDescription(bool extractAll) {
      if (extractAll) {
         return boost::locale::translate("doxy-text", "Here is a list of all module members with links "
                  "to the module documentation for each member:");
      } else {
         return boost::locale::translate("doxy-text", "Here is a list of all documented module members "
                  "with links to the modules they belong to:");
      }
   }

   /*! This is used in LaTeX as the title of the chapter with the
    *  index of all modules (Fortran).
    */
   std::string ModulesIndex() {
      return boost::locale::translate("doxy-text", "Modules Index");
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Module(bool first_capital, bool singular) {

      if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Module");
         } else  {
            return boost::locale::translate("doxy-text", "Modules");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "module");
         } else  {
            return boost::locale::translate("doxy-text", "modules");
         }
      }
   }

   /*! This is put at the bottom of a module documentation page and is
    *  followed by a list of files that were used to generate the page.
    */
   std::string GeneratedFromFilesFortran(ClassDef::CompoundType compType, bool single) {
      std::string result;

      switch (compType) {
         case ClassDef::Class:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this module was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this module was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Struct:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this type was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this type was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Union:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this union was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this union was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Interface:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this interface was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this interface was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Protocol:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this protocol was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this protocol was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Category:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this category was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this category was generated from "
                     "the following files:");
            }
            break;
         case ClassDef::Exception:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this exception was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this exception was generated from "
                     "the following files:");
            }
            break;
         default:
            if (single) {
               result = boost::locale::translate("doxy-text", "The documentation for this was generated from "
                     "the following file:");
            } else {
               result = boost::locale::translate("doxy-text", "The documentation for this was generated from "
                     "the following files:");
            }
            break;
      }
      return result;
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Type(bool first_capital, bool singular) {
       if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Type");
         } else  {
            return boost::locale::translate("doxy-text", "Types");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "type");
         } else  {
            return boost::locale::translate("doxy-text", "types");
         }
      }
   }

   /*! This is used for anslation of the word that will possibly
    *  be followed by a single name or by a list of names
    *  of the category.
    */
   std::string Subprogram(bool first_capital, bool singular) {
       if (first_capital) {

         if (singular) {
            return boost::locale::translate("doxy-text", "Subprogram");
         } else  {
            return boost::locale::translate("doxy-text", "Subprograms");
         }

      } else {

         if (singular) {
            return boost::locale::translate("doxy-text", "subprogram");
         } else  {
            return boost::locale::translate("doxy-text", "subprograms");
         }
      }
   }

   /*! C# Type Constraint list */
   std::string TypeConstraints() {
      return boost::locale::translate("doxy-text", "Type Constraints");
   }

   /*! directory relation for \a name */
   std::string DirRelation(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Relation")) % name;
   }

   /*! Loading message shown when loading search results */
   std::string Loading() {
      return boost::locale::translate("doxy-text", "Loading...");
   }

   /*! Label used for search results in the global namespace */
   std::string GlobalNamespace() {
      return boost::locale::translate("doxy-text", "Global Namespace");
   }

   /*! Message shown while searching */
   std::string Searching() {
      return boost::locale::translate("doxy-text", "Searching...");
   }

   /*! Text shown when no search results are found */
   std::string NoMatches() {
      return boost::locale::translate("doxy-text", "No Matches");
   }

   /*! when clicking a directory dependency label, a page with a
    *  table is shown. The heading for the first column mentions the
    *  source file that has a relation to another file.
    */
   std::string FileIn(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "File in %1%")) % (name);
   }

   /*! when clicking a directory dependency label, a page with a
    *  table is shown. The heading for the second column mentions the
    *  destination file that is included.
    */
   std::string IncludesFileIn(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "Includes file in %1%")) % (name);
   }

   /*! Header for the page with bibliographic citations */
   std::string CiteReferences() {
      return boost::locale::translate("doxy-text", "Bibliography");
   }

   /*! Text for copyright paragraph */
   std::string Copyright() {
      return boost::locale::translate("doxy-text", "Copyright");
   }

   /*! Header for the graph showing the directory dependencies */
   std::string DirDepGraph(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "Directory dependency graph for %1%:")) % (name);
   }

   /*! Detail level selector shown for hierarchical indices */
   std::string DetailLevel() {
      return boost::locale::translate("doxy-text", "detail level");
   }

   /*! Section header for list of template parameters */
   std::string TemplateParameters() {
      return boost::locale::translate("doxy-text", "Template Parameters");
   }

   /*! Used in dot graph when UML_LOOK is enabled and there are many fields */
   std::string AndMore(const std::string &number) {
      return boost::format(boost::locale::translate("doxy-text", "and %1% more...")) % (number);
   }

   /*! Used file list for a Java enum */
   std::string EnumGeneratedFromFiles(bool single) {
      if (single) {
         return boost::locale::translate("doxy-text", "The documentation for this enum was generated "
                  "from the following file:");
      } else {
         return boost::locale::translate("doxy-text", "The documentation for this enum was generated "
                  " from the following files:");
      }
   }

   /*! Header of a Java enum page (Java enums are represented as classes). */
   std::string EnumReference(const std::string &name) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Enum Reference")) % (name);
   }

   /*! Used for a section containing inherited members */
   std::string InheritedFrom(const std::string &members, const std::string &what) {
      return boost::format(boost::locale::translate("doxy-text", "%1% inherited from %2%")) % (members) % (what);
   }

   /*! Header of the sections with inherited members specific for the
    *  base class(es)
    */
   std::string AdditionalInheritedMembers() {
      return boost::locale::translate("doxy-text", "Additional Inherited Members");
   }

   /*! Used as a tooltip for the toggle button that appears in the
    *  navigation ee in the HTML output when GENERATE_TREEVIEW is
    *  enabled. This tooltip explains the meaning of the button.
    */
   std::string PanelSyncTooltip(bool enable) {
      if (enable) {
         return boost::locale::translate("doxy-text", "click to enable panel synchronization");
      } else {
         return boost::locale::translate("doxy-text", "click to disable panel synchronization");
      }
   }

   /*! Used in a method of an Objective-C class that is declared in a
    *  a category. Note that the @1 marker is required and is replaced
    *  by a link.
    */
   std::string ProvidedByCategory() {
      return boost::locale::translate("doxy-text", "Provided by category @1.");
   }

   /*! Used in a method of an Objective-C category that extends a class.
    *  Note that the @1 marker is required and is replaced by a link to
    *  the class method.
    */
   std::string ExtendsClass() {
      return boost::locale::translate("doxy-text", "Extends class @1");
   }

   /*! Used as the header of a list of class methods in Objective-C.
    *  These are similar to static public member functions in C++.
    */
   std::string ClassMethods() {
      return boost::locale::translate("doxy-text", "Class Methods");
   }

   /*! Used as the header of a list of instance methods in Objective-C.
    *  These are similar to public member functions in C++.
    */
   std::string InstanceMethods() {
      return boost::locale::translate("doxy-text", "Instance Methods");
   }

   /*! Used as the header of the member functions of an Objective-C class.
    */
   std::string MethodDocumentation() {
      return boost::locale::translate("doxy-text", "Method Documentation");
   }

   /*! Used as the title of the design overview picture created for the
    *  VHDL output.
    */
   std::string DesignOverview() {
      return boost::locale::translate("doxy-text", "Design Overview");
   }

   /** old style UNO IDL services: implemented interfaces */
   std::string Interfaces() {
      return boost::locale::translate("doxy-text", "Exported Interfaces");
   }

   /** old style UNO IDL services: inherited services */
   std::string Services() {
      return boost::locale::translate("doxy-text", "Included Services");
   }

   /** UNO IDL constant groups */
   std::string ConstantGroups() {
      return boost::locale::translate("doxy-text", "Constant Groups");
   }

   /** UNO IDL constant groups */
   std::string ConstantGroupReference(const std::string &namespaceName) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Constant Group Reference")) % (namespaceName);
   }

   /** UNO IDL service page title */
   std::string ServiceReference(const std::string &sName) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Service Reference")) % (sName);
   }

   /** UNO IDL singleton page title */
   std::string SingletonReference(const std::string &sName) {
      return boost::format(boost::locale::translate("doxy-text", "%1% Singleton Reference")) % (sName);
   }

   /** UNO IDL service page */
   std::string ServiceGeneratedFromFiles(bool single) {
      if (single) {
         return boost::locale::translate("doxy-text", "The documentation for this service "
                          "was generated from the following file:");

      } else {
        return boost::locale::translate("doxy-text", "The documentation for this service "
                          "was generated from the following files:");
      }
   }

   /** UNO IDL singleton page */
   std::string SingletonGeneratedFromFiles(bool single) {
      if (single) {
         return boost::locale::translate("doxy-text", "The documentation for this singleton "
                          "was generated from the following file:");

      } else {
        return boost::locale::translate("doxy-text", "The documentation for this singleton "
                          "was generated from the following files:");
      }
   }
};

#endif
