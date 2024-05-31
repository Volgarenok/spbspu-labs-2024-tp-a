#include "expressionTokens.hpp"

#include <stdexcept>
#include <utility>

zhalilov::InfixToken::InfixToken():
  binOperator_{},
  operand_{},
  bracket_{ PrimaryType::CloseBracket },
  varExpr_{},
  type_{ PrimaryType::Undefined }
{}

zhalilov::InfixToken::InfixToken(const InfixToken &tkn):
  InfixToken{}
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand_ = tkn.operand_;
    return;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket_ = Bracket(PrimaryType::OpenBracket);
    return;
  case PrimaryType::VarExpression:
    type_ = PrimaryType::VarExpression;
    varExpr_ = tkn.varExpr_;
    return;
  default:
    return;
  }
}

zhalilov::InfixToken::InfixToken(BinOperator aBinOperator):
  InfixToken{}
{
  binOperator_ = aBinOperator;
  type_ = PrimaryType::BinOperator;
}

zhalilov::InfixToken::InfixToken(Operand aOperand):
  InfixToken{}
{
  operand_ = aOperand,
    type_ = PrimaryType::Operand;
}

zhalilov::InfixToken::InfixToken(Bracket aBracket):
  bracket_(aBracket),
  type_(bracket_.getType())
{}

zhalilov::InfixToken::InfixToken(VarExpression aVarExpr):
  InfixToken{}
{
  varExpr_ = aVarExpr;
  type_ = PrimaryType::VarExpression;
}

zhalilov::InfixToken::~InfixToken()
{}

zhalilov::PrimaryType zhalilov::InfixToken::getType() const
{
  return type_;
}

zhalilov::BinOperator zhalilov::InfixToken::getBinOperator() const
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Operand zhalilov::InfixToken::getOperand() const
{
  if (type_ != PrimaryType::Operand)
  {
    throw std::logic_error("token doesn't store operand");
  }
  return operand_;
}

zhalilov::Bracket zhalilov::InfixToken::getBracket() const
{
  if (type_ != PrimaryType::CloseBracket && type_ != PrimaryType::OpenBracket)
  {
    throw std::logic_error("token doesn't store bracket");
  }
  return bracket_;
}

zhalilov::VarExpression zhalilov::InfixToken::getVarExpression() const
{
  if (type_ != PrimaryType::VarExpression)
  {
    throw std::logic_error("token doesn't store varexpr");
  }
  return varExpr_;
}

zhalilov::PostfixToken::PostfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::PostfixToken::PostfixToken(const PostfixToken &tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand_ = tkn.operand_;
    return;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
  default:
    return;
  }
}

zhalilov::PostfixToken::PostfixToken(BinOperator aBinOperator):
  binOperator_(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::PostfixToken::PostfixToken(Operand aOperand):
  operand_(aOperand),
  type_(PrimaryType::Operand)
{}

zhalilov::PrimaryType zhalilov::PostfixToken::getType() const
{
  return type_;
}

zhalilov::BinOperator zhalilov::PostfixToken::getBinOperator() const
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Operand zhalilov::PostfixToken::getOperand() const
{
  if (type_ != PrimaryType::Operand)
  {
    throw std::logic_error("token doesn't store operand");
  }
  return operand_;
}

zhalilov::TransferToken::TransferToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::TransferToken::TransferToken(const TransferToken &tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  default:
    return;
  }
}

zhalilov::TransferToken::TransferToken(BinOperator aBinOperator):
  binOperator_(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::TransferToken::TransferToken(Bracket aBracket):
  bracket_(aBracket),
  type_(aBracket.getType())
{}

zhalilov::PrimaryType zhalilov::TransferToken::getType() const
{
  return type_;
}

zhalilov::BinOperator zhalilov::TransferToken::getBinOperator() const
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Bracket zhalilov::TransferToken::getBracket() const
{
  if (type_ != PrimaryType::CloseBracket && type_ != PrimaryType::OpenBracket)
  {
    throw std::logic_error("token doesn't store bracket");
  }
  return bracket_;
}
