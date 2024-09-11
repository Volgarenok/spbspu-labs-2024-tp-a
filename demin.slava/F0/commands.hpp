#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace demin
{
  void showHelp();
  void read(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);

}

#endif
