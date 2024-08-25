#ifndef GETINFIX_HPP
#define GETINFIX_HPP

#include <iosfwd>
#include <list>

#include "expressionTokens.hpp"

namespace zhalilov
{
  void getInfix(std::list< InfixToken > &list, std::istream &in);
}

#endif
