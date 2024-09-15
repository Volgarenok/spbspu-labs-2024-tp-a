#include "infixToPostfix.hpp"

#include <stack>
#include <stdexcept>

#include "expressionTokens.hpp"

void zhalilov::infixToPostfix(std::list< InfixToken > &infix, std::list< PostfixToken > &postfix)
{
  std::stack< TransferToken > transfer;
  for (auto it = infix.cbegin(); it != infix.cend(); ++it)
  {
    if (it->getType() == PrimaryType::OpenBracket)
    {
      transfer.push(TransferToken(Bracket(PrimaryType::OpenBracket)));
    }
    else if (it->getType() == PrimaryType::CloseBracket)
    {
      while (transfer.top().getType() != PrimaryType::OpenBracket)
      {
        if (transfer.empty())
        {
          throw std::invalid_argument("incorrect bracket position");
        }
        postfix.push_back(PostfixToken(transfer.top().getBinOperator()));
        transfer.pop();
      }
      transfer.pop();
    }
    else if (it->getType() == PrimaryType::BinOperator)
    {
      while (!transfer.empty())
      {
        if (transfer.top().getType() != PrimaryType::BinOperator)
        {
          break;
        }
        if (transfer.top().getBinOperator() > it->getBinOperator())
        {
          break;
        }
        postfix.push_back(PostfixToken(transfer.top().getBinOperator()));
        transfer.pop();
      }
      transfer.push(TransferToken(it->getBinOperator()));
    }
    else
    {
      postfix.push_back(PostfixToken(it->getOperand()));
    }
  }
  while (!transfer.empty())
  {
    if (transfer.top().getType() == PrimaryType::OpenBracket)
    {
      throw std::invalid_argument("incorrect bracket position");
    }
    postfix.push_back(PostfixToken(transfer.top().getBinOperator()));
    transfer.pop();
  }
}
