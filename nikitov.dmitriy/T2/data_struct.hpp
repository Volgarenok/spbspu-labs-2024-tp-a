#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

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
}
#endif