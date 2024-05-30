#ifndef CMD_LINE_ARGS_HPP
#define CMD_LINE_ARGS_HPP

#include <ostream>
#include <string>
#include "commands.hpp"

namespace kravchenko
{
  void printHelp(std::ostream& out);
  void loadDict(const char* name, DictionaryMap& data);
  bool checkFile(const char* name);
}

#endif
