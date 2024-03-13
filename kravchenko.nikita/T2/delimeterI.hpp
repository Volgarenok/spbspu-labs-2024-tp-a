#ifndef DELIMETER_I_HPP
#define DELIMETER_I_HPP

#include <istream>
#include <string>

namespace kravchenko
{
  struct DelimeterI
  {
    const char expected;
    bool caseIgnore = false;
  };
  std::istream& operator>>(std::istream& in, DelimeterI&& exp);

  struct StringDelimeterI
  {
    const char* expected;
    bool caseIgnore = false;
  };
  std::istream& operator>>(std::istream& in, StringDelimeterI&& exp);
}

#endif
