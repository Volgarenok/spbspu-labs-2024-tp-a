#ifndef CMDS_HPP
#define CMDS_HPP
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

namespace altun
{
  void createDictionary(std::istream&, std::map< std::string, std::map < std::string, std::vector< std::string > > >&);
  void deleteDictionary(std::istream&, std::map< std::string, std::map < std::string, std::vector< std::string > > >&);
  void addWord(std::istream&, std::map< std::string, std::map < std::string, std::vector< std::string > > >&);
  void removeWord(std::istream&, std::map< std::string, std::map < std::string, std::vector< std::string > > >&);
}
#endif
