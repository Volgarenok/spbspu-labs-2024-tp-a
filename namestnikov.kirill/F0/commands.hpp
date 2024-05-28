#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <unordered_map>

namespace namestnikov
{
  void doHelp(std::ostream & out);
  void doCreate(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doAdd(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doFind(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doRemove(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doUnique(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doMerge(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doExport(std::istream & in, const std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap);
  void doImport(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap);
  void doPrefix(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doPostfix(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doSuffix(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
  void doPalindrome(std::istream & in, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap, std::ostream & out);
}

#endif
