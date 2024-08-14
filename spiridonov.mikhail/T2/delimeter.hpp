#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>
#include <string>

namespace spiridonov
{
  struct DelimeterChar
  {
    char expected;
  };

  struct DelimeterString
  {
    std::string expected;
  };

  struct UllLiteralIO
  {
    unsigned long long& expected;
  };

  std::istream& operator>>(std::istream& in, DelimeterChar&& exp);
  std::istream& operator>>(std::istream& in, DelimeterString&& exp);
  std::istream& operator>>(std::istream& in, UllLiteralIO&& exp);

}

#endif
