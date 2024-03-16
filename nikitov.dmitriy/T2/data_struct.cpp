#include <fstream>
#include <cmath>
#include "data_struct.hpp"
#include "delimiter.hpp"

bool nikitov::DataStruct::operator<(const DataStruct& other) const
{
  double ownComplex = std::pow(2, key2.real()) + std::pow(2, key2.imag());
  double otherComplex = std::pow(2, other.key2.real()) + std::pow(2, other.key2.imag());
  if (key1 == other.key1)
  {
    if (ownComplex == otherComplex)
    {
      return (key3.length() <= other.key3.length());
    }
    else
    {
      return ownComplex < otherComplex;
    }
  }
  else
  {
    return key1 < other.key1;
  }
}

std::istream& nikitov::operator>>(std::istream& input, DataStruct& value)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    using DelStr = DelimiterString;
    using DelChar = DelimiterChar;

    size_t keyNum = 0;
    input >> DelChar({'('});
    for (size_t i = 0; i != 3; ++i)
    {
      input >> DelStr({":key"}) >> keyNum;
      if (keyNum == 1)
      {
        input >> DelChar({'\''}) >> value.key1 >> DelChar({'\''});
      }
      else if (keyNum == 2)
      {
        double real = 0.0;
        double imag = 0.0;
        input >> DelStr({"#c("}) >> real >> imag >> DelChar({')'});
        value.key2 = { real, imag };
      }
      else if (keyNum == 3)
      {
        input >> DelChar({'\"'});
        std::getline(input, value.key3, '\"');
      }
    }
    input >> DelStr({":)"});
  }
  return input;
}

std::ostream& nikitov::operator<<(std::ostream& output, const DataStruct& value)
{
  std::ostream::sentry guard(output);
  if (guard)
  {
    output << value.key1 << value.key2 << value.key3;
  }
  return output;
}
