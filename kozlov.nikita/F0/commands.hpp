#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace kozlov
{
  void doCmdHelp(std::map< std::string, std::map< std::string, size_t > > dict, std::istream& in, std::ostream& out);
  void doCmdCreate(std::map< std::string, std::map< std::string, size_t > > dict, std::istream& in, std::ostream& out);
}
#endif
