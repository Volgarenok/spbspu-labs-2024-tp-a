#ifndef FORMATS_HPP
#define FORMATS_HPP

#include <istream>
#include <string>

namespace gladyshev
{
  struct CharKey
  {
    char& key;
  };
  struct SciKey
  {
    double& key;
  };
  struct StrKey
  {
    std::string& key;
  };
  std::istream& operator>>(std::istream& in, CharKey&& value);
  std::istream& operator>>(std::istream& in, SciKey&& value);
  std::istream& operator>>(std::istream& in, StrKey&& value);
}

#endif
