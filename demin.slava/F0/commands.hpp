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
  void out(std::map< std::string, std::vector< std::string > > &refs, std::istream &in, std::ostream &out);
  void add(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);
  void remove(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);
  void deleteList(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);
  void find(std::map< std::string, std::vector< std::string > > &refs, std::istream &in, std::ostream &out);
  void combine(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);
  void change(std::map< std::string, std::vector< std::string > > &refs, std::istream &in);
}

#endif
