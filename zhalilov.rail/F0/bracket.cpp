#include "bracket.hpp"

#include <stdexcept>

zhalilov::Bracket::Bracket(PrimaryType type):
  type_(type)
{}

zhalilov::Bracket::Bracket(char symb)
{
  if (symb == '(')
  {
    type_ = PrimaryType::OpenBracket;
  }
  else if (symb == ')')
  {
    type_ = PrimaryType::CloseBracket;
  }
  else
  {
    throw std::invalid_argument("symbol isn't scope");
  }
}

zhalilov::PrimaryType zhalilov::Bracket::getType() const
{
  return type_;
}
