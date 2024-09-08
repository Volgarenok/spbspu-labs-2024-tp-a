#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <string>
#include <queue>
#include <map>
#include <string>
#include <functional>

#include "token.hpp"

namespace rebdev
{
  using unary = std::map < std::string, std::function< double(const double &) > >;
  using binary = std::map < std::string, std::function< double(const double &, const double &) > >;
  using user = std::map < std::string, std::function< void(std::string, unary &, binary &) > >;
  using tokQueue = std::queue< token >;
  void makePostFix(std::string & str, tokQueue & queue, unary & unaryMap, binary & binaryMap, const user & userMap);
  double postFixToResult(tokQueue & queue);
}

#endif
