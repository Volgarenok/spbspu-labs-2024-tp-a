#include "calculateExpr.hpp"

#include <stack>
#include <stdexcept>

#include "expressionTokens.hpp"

long long zhalilov::calculateExpr(const std::list< PostfixToken > &expr)
{
  std::stack< Operand > operands;
  for (auto it = expr.cbegin(); it != expr.cend(); ++it)
  {
    if (it->getType() == PrimaryType::BinOperator)
    {
      if (operands.size() < 2)
      {
        throw std::invalid_argument("incorrect expression");
      }
      Operand last = operands.top();
      operands.pop();
      Operand nextToLast = operands.top();
      operands.pop();
      operands.push(it->getBinOperator()(nextToLast, last));
    }
    else
    {
      operands.push(it->getOperand());
    }
  }
  if (operands.size() != 1)
  {
    throw std::invalid_argument("incorrect expression");
  }
  return operands.top().getNum();
}
