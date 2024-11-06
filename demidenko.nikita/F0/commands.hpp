#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "dictionary.hpp"
namespace demidenko
{
  void doHelpCmd(std::ostream& out);
  void doCheckCmd(std::ostream& out, const char* fileName);
  void doAddCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doRemoveCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doSaveCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doLoadCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doListCmd(std::ostream& out, std::map< std::string, Dictionary >& dictionaries);
  void doTranslateCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries);
  void doSearchCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries);
  void doPrefixCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries);
  void doMergeCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doExcludeCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
  void doSplitCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries);
}

#endif
