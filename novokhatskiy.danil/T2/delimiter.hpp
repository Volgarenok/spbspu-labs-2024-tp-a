#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace novokhatskiy
{
  struct Delimiter
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, Delimiter&& ex);

  struct DelimiterAlpha
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterAlpha&& ex);

  struct DelimiterString
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& ex);

  struct DelimiterAlphaString
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterAlphaString&& ex);
}

#endif 
