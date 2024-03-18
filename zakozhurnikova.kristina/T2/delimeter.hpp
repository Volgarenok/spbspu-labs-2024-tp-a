#ifndef DELIMETERS_HPP
#define DELIMETERS_HPP

namespace zakozhurnikova
{
  struct Delimeter
  {
    char expected;
  }
;
  std::istream& operator>>(std::istream& in, const DelimiterI& exp);
}
#endif
