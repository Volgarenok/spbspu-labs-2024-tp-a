#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "Dictionary.hpp"

namespace erfurt
{
  void makeInsert(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeFindTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeDelete(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeMerge(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeAddTranslate(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makePrint(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeCommon(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeUnique(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeIsTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeHelp(std::ostream & out);
  void makePrintDictionaries(std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeSave(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeOpen(std::istream & in, std::vector< Dictionary > & dictionaries);
  void makeCreate(std::istream & in, std::vector< Dictionary > & dictionaries);
}

#endif
