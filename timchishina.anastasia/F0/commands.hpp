#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace timchishina
{
  void doHelp(std::ostream& out);
  void doCreate(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
}
#endif
