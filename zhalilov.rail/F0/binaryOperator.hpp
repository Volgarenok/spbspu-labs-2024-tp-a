#ifndef BINARYOPERATOR_HPP
#define BINARYOPERATOR_HPP

namespace zhalilov
{
  class Operand;

  class BinOperator
  {
  public:
    enum class Type
    {
      Undefined,
      Addition,
      Subtraction,
      Multiplication,
      Division,
      Mod
    };

    BinOperator();
    explicit BinOperator(Type);
    explicit BinOperator(char symb);
    Operand operator()(const Operand &, const Operand &) const;

    bool operator<(const BinOperator &other) const;
    bool operator>(const BinOperator &other) const;
    bool operator==(const BinOperator &other) const;
    bool operator!=(const BinOperator &other) const;
    bool operator<=(const BinOperator &other) const;
    bool operator>=(const BinOperator &other) const;

    Type getType() const;

  private:
    Type type_;

    unsigned short getPriority() const;
    Operand doAddition(const Operand &, const Operand &) const;
    Operand doSubstraction(const Operand &, const Operand &) const;
    Operand doMultiplication(const Operand &, const Operand &) const;
    Operand doDivision(const Operand &, const Operand &) const;
    Operand doMod(const Operand &, const Operand &) const;
  };
}

#endif
