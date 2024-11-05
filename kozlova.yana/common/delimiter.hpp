#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>
#include <cstring>

namespace kozlova
{
  struct DelimiterCharIO
  {
      char delimiter;
  };

  struct DelimiterStringIO
  {
      const char* delimiter;
  };

  std::istream & operator>>(std::istream & in, DelimiterCharIO && dest);
  std::istream & operator>>(std::istream & in, DelimiterStringIO && dest);
}

#endif
