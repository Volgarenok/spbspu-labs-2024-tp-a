#ifndef FORMATS_HPP
#define FORMATS_HPP

#include <iostream>

namespace stepanchenko
{
  struct CharI
  {
    char& char_key;
  };

  struct LongLongI
  {
    long long& longlong_key;
  };

  struct StringI
  {
    std::string& string_key;
  };

  std::istream& operator>>(std::istream& in, CharI&& ch);
  std::istream& operator>>(std::istream& in, LongLongI&& ch);
  std::istream& operator>>(std::istream& in, StringI&& str);
}

#endif
