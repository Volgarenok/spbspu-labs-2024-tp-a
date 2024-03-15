#ifndef PARSE_KEYS_HPP
#define PARSE_KEYS_HPP
#include <istream>
#include <string>

namespace novokhatskiy
{
  struct UnsignedLLKey
  {
    unsigned long long &key1;
  };
  std::istream &operator>>(std::istream &in, UnsignedLLKey &&tmp);

  struct PairKey
  {
    std::pair<long long, unsigned long long> &key2;
  };
  std::istream &operator>>(std::istream &in, PairKey &&tmp);

  struct StringKey
  {
    std::string &key3;
  };
  std::istream &operator>>(std::istream &in, StringKey &&tmp);
}
#endif