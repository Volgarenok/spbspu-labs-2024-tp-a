#ifndef DELIMETER_I_HPP
#define DELIMETER_I_HPP

#include <istream>
#include <string>

namespace kravchenko
{
  struct DelimeterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimeterI&& exp);

  struct AnyCaseDelimeterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, AnyCaseDelimeterI&& exp);

  struct StringDelimeterI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimeterI&& exp);

  struct AnyCaseStringDelimeterI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream& in, AnyCaseStringDelimeterI&& exp);
}

#endif
