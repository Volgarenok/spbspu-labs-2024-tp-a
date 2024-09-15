#ifndef EXPRESSIONTOKENS_HPP
#define EXPRESSIONTOKENS_HPP

#include "primaryType.hpp"
#include "bracket.hpp"
#include "operand.hpp"
#include "binaryOperator.hpp"
#include "varExpression.hpp"

namespace zhalilov
{
  struct InfixToken
  {
    InfixToken();
    InfixToken(const InfixToken &tkn);
    explicit InfixToken(BinOperator aBinOperator);
    explicit InfixToken(Operand aOperand);
    explicit InfixToken(Bracket aBracket);
    explicit InfixToken(VarExpression aVarExpr);
    ~InfixToken();

    PrimaryType getType() const;

    BinOperator getBinOperator() const;
    Operand getOperand() const;
    Bracket getBracket() const;
    VarExpression getVarExpression() const;

  private:
    BinOperator binOperator_;
    Operand operand_;
    Bracket bracket_;
    VarExpression varExpr_;

    PrimaryType type_;
  };

  struct PostfixToken
  {
    PostfixToken();
    PostfixToken(const PostfixToken &tkn);
    explicit PostfixToken(BinOperator aBinOperator);
    explicit PostfixToken(Operand aOperand);

    PrimaryType getType() const;

    BinOperator getBinOperator() const;
    Operand getOperand() const;

  private:
    union
    {
      BinOperator binOperator_;
      Operand operand_;
    };

    PrimaryType type_;
  };

  struct TransferToken
  {
    TransferToken();
    TransferToken(const TransferToken &tkn);
    explicit TransferToken(BinOperator aBinOperator);
    explicit TransferToken(Bracket aBracket);

    PrimaryType getType() const;

    BinOperator getBinOperator() const;
    Bracket getBracket() const;

  private:
    union
    {
      BinOperator binOperator_;
      Bracket bracket_;
    };

    PrimaryType type_;
  };
}

#endif
