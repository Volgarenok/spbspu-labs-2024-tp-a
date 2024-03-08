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

  struct StringDelimeterI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimeterI&& exp);
}

#endif
