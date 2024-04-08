#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace baranov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string & ref;
  }

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
}

#endif

