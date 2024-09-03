#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <string>
#include <queue>

#include "token.hpp"

namespace rebdev
{
  void makePostFix(std::string & str, std::queue< token > & queue);
  long long postFixToResult(std::queue< token > & queue);
}

#endif
