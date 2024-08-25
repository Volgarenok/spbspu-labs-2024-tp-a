#ifndef DELIMETR_H
#define DELIMETR_H

#include <iostream>

namespace kartamyshev
{
  struct DelimiterSym
  {
    char expected;
  };

  struct DelimiterStr
  {
  const char* expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterSym&& exp);
  std::istream& operator>>(std::istream& in, DelimiterStr&& exp);
}
#endif
