#ifndef KEYS_H
#define KEYS_H

#include <iostream>
#include <string>

namespace kazennov
{
  struct CharKey
  {
    char& c;
  };
  struct RatKey
  {
    std::pair< long long, unsigned long long >& rat;
  };
  struct StrKey
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, CharKey&& key);
  std::istream& operator>>(std::istream& in, RatKey&& key);
  std::istream& operator>>(std::istream& in, StrKey&& key);
}
#endif
