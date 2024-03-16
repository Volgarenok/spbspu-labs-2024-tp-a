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
    //using DelStr = DelimiterString;
    //using DelChar = DelimiterChar;

    double real = 0.0;
    double imag = 0.0;

     input >> value.key1 >> real >> imag >> value.key3;
     value.key2 = {real, imag};
    /*input >> DelStr({"(:key1"}) >> DelChar({'\''}) >> value.key1 >> DelChar({'\''}) >>
      DelStr({":key2"}) >> DelStr({"#c("}) >> real >> imag >> DelStr({"):key3"}) >>
      DelChar({'\"'}) >> value.key3 >> DelStr({"\":"});
    value.key2 = {real, imag};*/
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
