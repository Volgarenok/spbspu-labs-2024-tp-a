#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "Dictionary.hpp"

namespace erfurt
{
  void makeInsert(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeFindTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeDelete(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeMerge(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeAddTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makePrint(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeCommon(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeUnique(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeIsTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeHelp(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makePrintDictionaries(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeSave(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeOpen(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
  void makeCreate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out);
}

#endif
