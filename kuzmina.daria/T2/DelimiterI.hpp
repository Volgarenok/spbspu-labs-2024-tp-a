#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <iostream>
#include <string>

namespace kuzmina
{
  struct DelimiterI
  {
    char expected;
  };

  struct DelimiterIStr
  {
    const char* expected;
  };

  struct SLLKey
  {
    long long & value;
  };

  struct RATKey
  {
    std::pair< long long, unsigned long long > & value;
  };

  struct STRKey
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream&, DelimiterI&&);
  std::istream& operator>>(std::istream&, DelimiterIStr&&);
  std::istream& operator>>(std::istream&, SLLKey&&);
  std::istream& operator>>(std::istream&, RATKey&&);
  std::istream& operator>>(std::istream&, STRKey&&);
}

#endif
