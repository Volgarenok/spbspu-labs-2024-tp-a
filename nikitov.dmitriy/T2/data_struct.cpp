#include <fstream>
#include "data_struct.hpp"
#include "delimiter.hpp"

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
