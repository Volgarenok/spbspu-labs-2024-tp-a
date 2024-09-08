#ifndef USERCOMMANDS_HPP
#define USERCOMMANDS_HPP

#include <string>
#include <functional>
#include <map>

namespace rebdev
{
  using unary = std::map < std::string, std::function< double(const double &) > >;
  using binary = std::map < std::string, std::function< double(const double &, const double &) > >;
  void add(std::string str, unary & unaryMap, binary & binaryMap);
  void replace(std::string str, unary & unaryMap, binary & binaryMap);
  void importFile(std::string str, unary & unaryMap, binary & binaryMap);
  void exportFile(std::string str, unary & unaryMap, binary & binaryMap);
}
#endif
