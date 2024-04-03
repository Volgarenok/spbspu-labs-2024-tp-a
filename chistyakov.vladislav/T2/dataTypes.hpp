#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <iostream>
#include <utility>
#include <cstring>

namespace chistyakov
{
  struct UllBin
  {
    unsigned long long & binaryNumber;
  };
  std::istream & operator>>(std::istream & in, UllBin && binNum);

  struct RatLsp
  {
    std::pair< long long, unsigned long long > & pairLlAndUll;
  };
  std::istream & operator>>(std::istream & in, RatLsp && pair);

  struct StringT
  {
    std::string str;
  };
  std::istream & operator>>(std::istream&, StringT && str);
}

#endif
