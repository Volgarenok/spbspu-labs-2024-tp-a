#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>
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

  std::istream& operator>>(std::istream& in, DelimiterCharIO&& dest);
  std::istream& operator>>(std::istream& in, DelimiterStringIO&& dest);
}
#endif
