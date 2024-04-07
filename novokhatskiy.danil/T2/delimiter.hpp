#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace novokhatskiy
{
  template < bool caseChecking >
  struct Delimiter
  {
    const char expected;
  };

  template < bool caseChecking >
  std::istream& operator>>(std::istream& in, Delimiter< caseChecking >&& ex);

  template < bool caseChecking >
  struct DelimiterString
  {
    const char* expected;
  };

  template < bool caseChecking >
  std::istream& operator>>(std::istream& in, DelimiterString< caseChecking >&& ex);

}

#endif
