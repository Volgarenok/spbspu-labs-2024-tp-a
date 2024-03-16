#include <fstream>
#include "data_struct.hpp"
#include "delimiter.hpp"

std::istream& nikitov::DataStruct::operator>>(std::istream& input)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    using DelStr = DelimiterString;
    using DelChar = DelimiterChar;

    double real = 0.0;
    double imag = 0.0;

    input >> DelStr({"(:key1"}) >> DelChar({'\''}) >> key1 >> DelChar({'\''}) >> 
      DelStr({":key2"}) >> DelStr({"#c("}) >> real >> imag >> DelStr({"):key3"}) >>
      DelChar({'\"'}) >> key3 >> DelStr({"\":"});
    key2 = {real, imag};
  }
  return input;
}
