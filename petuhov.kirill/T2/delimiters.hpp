#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <iostream>

namespace petuhov {
  struct DelimiterIO {
    char expected;
  };

  struct UllHexIO {
    unsigned long long &ref;
  };

  struct StringIO {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&del);
  std::istream &operator>>(std::istream &in, UllHexIO &&ullhex);
  std::ostream &operator<<(std::ostream &out, UllHexIO &&ullhex);
  std::istream &operator>>(std::istream &in, StringIO &&str);
  std::ostream &operator<<(std::ostream &out, StringIO &&str);
}

#endif
