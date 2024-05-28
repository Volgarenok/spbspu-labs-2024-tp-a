#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include "Dictionary.hpp"

namespace chernikova
{
  void doCommand(std::map< std::string, Dictionary >& dataBase, const std::string& command);
  void readData(std::map< std::string, Dictionary >& dataBase, std::istream& input);

}

#endif
