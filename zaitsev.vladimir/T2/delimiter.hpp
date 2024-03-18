#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>

namespace zaitsev
{
  struct CharDelimiter
  {
    const char val;
  };

  std::istream& operator>>(std::istream& in, const CharDelimiter&& exp);
}
#endif 
