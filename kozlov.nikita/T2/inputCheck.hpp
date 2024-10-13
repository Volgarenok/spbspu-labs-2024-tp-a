#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>

namespace kozlov
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp);

  struct Label
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, Label&& exp);
}
#endif
