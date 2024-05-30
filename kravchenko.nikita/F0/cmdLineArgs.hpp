#ifndef CMD_LINE_ARGS_HPP
#define CMD_LINE_ARGS_HPP

#include <ostream>
#include <string>
#include "commands.hpp"

namespace kravchenko
{
  void printHelp(std::ostream& out);
  void loadDict(const std::string& name, DictionaryMap& data);
  void checkFile(const std::string& name, std::ostream& out);
}

#endif
