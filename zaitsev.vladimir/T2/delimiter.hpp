#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>

namespace zaitsev
{
  struct Delimiter
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const Delimiter&& exp);
}
#endif
