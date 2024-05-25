#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
}
#endif