#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <string>
#include <map>

namespace gladyshev
{
  using dic = std::map< std::string, int >;
  using mainDic = std::map< std::string, dic >;
  bool toErase(const std::pair< std::string, int >& pair);
  std::pair< std::string, int > updatePair(const std::pair< std::string, int >& d1pair, const dic& dict2);
  std::pair< std::string, int > updatePairPlus(const std::pair< std::string, int >& d1pair, const dic& dict2);
  std::pair< std::string, int > updatePairMinus(const std::pair< std::string, int >& d1pair, const dic& dict2);
  void print_dictionary(const dic& dictionary, std::ostream& out);
  void deleteDict(mainDic& dictionaries, std::istream& in);
  void deleteName(mainDic& dictionaries, std::istream& in);
  void save(const mainDic& dictionaries, std::istream& in);
  void print_dictionaryL(const dic& dictionary, int n, std::ostream& out);
  void print_dictionariesL(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  void print_dictionaries(const mainDic& dictionaries, std::istream& in, std::ostream& out);
  dic intersectImpl(const dic& dict1, const dic& dict2);
  void printInfo(std::ostream& out);
  bool inOther(const dic& dict1, const std::pair< std::string, int >& dict2);
  void intersect(mainDic& dictionaries, std::istream& in);
  void addelem(mainDic& dictionaries, std::istream& in);
  void addition(mainDic& dictionaries, std::istream& in);
  dic additionImpl(const dic& dict1, const dic& dict2);
  void complement(mainDic& dictionaries, std::istream& in);
  dic complementImpl(const dic& dict1, const dic& dict2);
}

#endif
