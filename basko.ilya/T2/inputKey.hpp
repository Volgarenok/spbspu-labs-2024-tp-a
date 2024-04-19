#ifndef INPUT_KEY_H
#define INPUT_KEY_H

#include <string>
#include <complex>
#include <iostream>

namespace basko
{
  struct UllHexKey
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, UllHexKey&& data);

  struct CmpLspKey
  {
    std::complex< double >& value;
  };
  std::istream& operator>>(std::istream& in, CmpLspKey&& data);

  struct StringKey
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StringKey&& data);
}

#endif
