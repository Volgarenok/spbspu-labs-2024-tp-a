#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <fstream>
#include <string>
#include <complex>

namespace nikitov
{
  struct DataStruct
  {
    char key1;
    std::complex< double > key2;
    std::string key3;
  };

  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& input, Delimiter delimiter);
}


#endif
