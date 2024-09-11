#ifndef PRIMARYTYPE_HPP
#define PRIMARYTYPE_HPP

namespace zhalilov
{
  enum class PrimaryType
  {
    BinOperator,
    Operand,
    VarExpression,
    OpenBracket,
    CloseBracket,
    Undefined
  };
}

#endif
