#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <istream>

namespace ibragimov
{
  struct DelimiterI
  {
    const char* expectation;
  };
  std::istream& operator>>(std::istream&, const DelimiterI&&);

  struct IgnoreCaseDelimiterI
  {
    const char* expectation;
  };
  std::istream& operator>>(std::istream&, const IgnoreCaseDelimiterI&&);
}

#endif
