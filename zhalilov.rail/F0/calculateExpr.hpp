#ifndef CALCULATEEXPR_HPP
#define CALCULATEEXPR_HPP

#include <list>

namespace zhalilov
{
  struct PostfixToken;
  long long calculateExpr(const std::list< PostfixToken > &expr);
}

#endif
