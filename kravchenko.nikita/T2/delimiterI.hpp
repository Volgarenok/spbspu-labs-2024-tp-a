#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>
#include <string>

namespace kravchenko
{
  struct DelimiterI
  {
    const char expected;
    bool caseIgnore = false;
  };
  std::istream& operator>>(std::istream& in, DelimiterI&& exp);

  struct StringDelimiterI
  {
    const char* expected;
    bool caseIgnore = false;
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& exp);
}

#endif
