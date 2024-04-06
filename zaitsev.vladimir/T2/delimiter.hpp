#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>

namespace zaitsev
{
  struct CharDelimiter
  {
    const char expected;
  };

  struct StrDelimiter
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, const CharDelimiter&& exp);
  std::istream& operator>>(std::istream& in, const StrDelimiter&& exp);
}
#endif
