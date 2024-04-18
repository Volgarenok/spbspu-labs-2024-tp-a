#ifndef NAME_OF_KEYS_HPP
#define NAME_OF_KEYS_HPP

#include <istream>
#include <string>

namespace skuratov
{
  struct UllKey
  {
    unsigned long long& num;
  };
  std::istream& operator>>(std::istream& in, UllKey&& key);

  struct CharKey
  {
    char& num;
  };
  std::istream& operator>>(std::istream& in, CharKey&& key);

  struct StringKey
  {
    std::string& string;
  };
  std::istream& operator>>(std::istream& in, StringKey&& key);
}

#endif
