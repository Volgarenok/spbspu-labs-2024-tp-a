#ifndef FORMATS_HPP
#define FORAMTS_HPP
#include <iostream>
#include <string>
#include <utility>

namespace skopchenko
{
  struct RatLsp
  {
    std::pair< long long, unsigned long long >& value;
  };
  std::istream& operator>>(std::istream& in, RatLsp&& num);

  struct SllLit
  {
    long long& value;
  };
  std::istream& operator>>(std::istream& in, SllLit&& num);

  struct StringKey
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringKey&& num);
}
#endif
