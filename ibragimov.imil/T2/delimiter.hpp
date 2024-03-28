#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace ibragimov
{
  struct CharDelimiterI
  {
    const char expected;
  };
  std::istream& operator>>(std::istream&, const CharDelimiterI&&);

  struct AnyCaseCharDelimiterI
  {
    const char expected;
  };
  std::istream& operator>>(std::istream&, const AnyCaseCharDelimiterI&&);

  struct StringDelimiterI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream&, const StringDelimiterI&&);

}

#endif
