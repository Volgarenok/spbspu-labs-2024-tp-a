#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>

#include "Dictionary.hpp"

namespace ayupov
{
  void doHelp(std::ostream& out);
  void doCreate(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doInsert(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doPrint(std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out);
  void doSearch(std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out);
  void doDeleteWord(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doDeleteTranslation(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doDeleteDictionary(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doSame(std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out);
  void doMerge(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doIntersection(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doSize(std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out);
  void doImport(std::map< std::string, ARDictionary >& dicts, std::istream& in);
  void doExport(std::map< std::string, ARDictionary >& dicts, std::istream& in);
}

#endif
