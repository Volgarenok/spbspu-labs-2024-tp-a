#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <string>
#include <map>

namespace gladyshev
{
  using dic = std::map< std::string, int >;
  using mainDic = std::map< std::string, dic >;
  void deleteDict(mainDic& dictionaries, std::istream& in);
  void deleteName(mainDic& dictionaries, std::istream& in);
  void save(const mainDic& dictionaries, std::istream& in);
  void print_dictionariesL(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  void print_dictionaries(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  void printInfo(std::ostream& out);
  bool inOther(const dic& dict1, const std::pair< std::string, int >& dict2);
  void intersect(mainDic& dictionaries, std::istream& in);
  void addelem(mainDic& dictionaries, std::istream& in);
  void addition(mainDic& dictionaries, std::istream& in);
  void complement(mainDic& dictionaries, std::istream& in);
}

#endif
