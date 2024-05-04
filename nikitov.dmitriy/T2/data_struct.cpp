#include "data_struct.hpp"
#include <istream>
#include <iomanip>
#include <cmath>
#include "delimiter.hpp"
#include "scope_guard.hpp"

bool nikitov::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else
  {
    if (std::abs(key2) != std::abs(other.key2))
    {
      return std::abs(key2) < std::abs(other.key2);
    }
    else
    {
      return (key3.length() <= other.key3.length());
    }
  }
}

std::istream& nikitov::operator>>(std::istream& input, DataStruct& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

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
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  input >> DelStr({":)"});
  return input;
}

std::ostream& nikitov::operator<<(std::ostream& output, const DataStruct& value)
{
  std::ostream::sentry guard(output);
  if (!guard)
  {
    return output;
  }

  ScopeGuard scopeGuard(output);
  output << std::setprecision(1) << std::fixed;
  output << '(';
  output << ":key1 " << '\'' << value.key1 << '\'';
  output << ":key2 " << "#c(" << value.key2.real() << ' ' << value.key2.imag() << ')';
  output << ":key3 " << '\"' << value.key3 << '\"';
  output << ":)";
  return output;
}
