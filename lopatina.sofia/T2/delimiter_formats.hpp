#ifndef DELIMITER_FORMATS_HPP
#define DELIMITER_FORMATS_HPP

#include <istream>
#include <string>
namespace lopatina
{
  struct DelimiterIO
  {
    char exp;
  };

  struct UllLiteralIO
  {
    unsigned long long & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, UllLiteralIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
}

#endif
