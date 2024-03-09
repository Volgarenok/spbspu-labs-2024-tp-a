#ifndef DELIMETER_I_HPP
#define DELIMETER_I_HPP

#include <istream>
#include <string>

namespace kravchenko
{
  struct DelimeterI
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, DelimeterI&& exp);

  struct AnyCaseDelimeterI
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, AnyCaseDelimeterI&& exp);

  struct StringDelimeterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimeterI&& exp);

  struct AnyCaseStringDelimeterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, AnyCaseStringDelimeterI&& exp);
}

#endif
