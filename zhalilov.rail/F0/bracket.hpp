#ifndef BRACKET_HPP
#define BRACKET_HPP

#include "primaryType.hpp"

namespace zhalilov
{
  class Bracket
  {
  public:
    explicit Bracket(PrimaryType type);
    explicit Bracket(char symb);
    PrimaryType getType() const;

  private:
    PrimaryType type_;
  };
}

#endif
