#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <iostream>

namespace petuhov {
  struct DelimiterIO {
  char expected;
  };

  struct UllLiteralIO {
    unsigned long long &ref;
  };

  struct StringIO {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &del);
  std::istream &operator>>(std::istream &in, UllLiteralIO &ull);
  std::istream &operator>>(std::istream &in, StringIO &str);
}

#endif
