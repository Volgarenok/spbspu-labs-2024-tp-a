#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include <list>

namespace zhalilov
{
  class InfixToken;
  class PostfixToken;
  void infixToPostfix(std::list< InfixToken > &infix, std::list< PostfixToken > &postfix);
}

#endif
