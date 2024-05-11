#ifndef DELIMETERS_HPP
#define DELIMETERS_HPP

#include <iostream>

namespace stepanchenko
{
  struct DelimiterI
  {
    const char expected;
  };

  struct StringDelimiterI
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterI&& del);
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);
}

#endif
