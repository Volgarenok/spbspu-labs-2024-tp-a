#ifndef INPUT_KEYS_HPP
#define INPUT_KEYS_HPP

#include <istream>
#include <string>
#include <utility>

namespace novokhatskiy
{
  struct BinKey
  {
    unsigned long long& value;
  };

  std::istream& operator>>(std::istream& in, BinKey&& key);

  struct RATKey
  {
    std::pair< long long, unsigned long long >& pair;
  };

  std::istream& operator>>(std::istream& in, RATKey&& key);

  struct STRKey
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, STRKey&& key);
}

#endif
