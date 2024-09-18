#ifndef CMDS_HPP
#define CMDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace strelyaev
{
  void addDictionary(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void deleteDictionary(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void addWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void removeWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void translate(std::ostream&, std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void mergeDictionaries(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void getIntersection(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void getCombining(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void getDifference(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
}

#endif
