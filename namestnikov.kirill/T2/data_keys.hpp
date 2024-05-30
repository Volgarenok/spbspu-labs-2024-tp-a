#ifndef DATA_KEYS_HPP
#define DATA_KEYS_HPP

#include <istream>
#include <string>

namespace namestnikov
{
  struct DblKey
  {
    double & data;
  };
  struct OctKey
  {
    unsigned long long & data;
  };
  struct StrKey
  {
    std::string & data;
  };
  std::istream & operator>>(std::istream & in, DblKey && key);
  std::istream & operator>>(std::istream & in, OctKey && key);
  std::istream & operator>>(std::istream & in, StrKey && key);
}

#endif
