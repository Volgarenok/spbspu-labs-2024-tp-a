#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iosfwd>
#include <string>

namespace arakelyan
{
  struct DelimiterIO
  {
    char exp;
  };

  struct LableIO
  {
    std::string exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, LableIO &&dest);
}

#endif
