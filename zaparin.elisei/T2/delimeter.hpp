#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace zaparin
{
  struct Delimeter
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, Delimeter&& exp);

  struct KeyType
  {
    size_t& value;
  };

  std::istream& operator>>(std::istream& in, KeyType&& exp);

}

#endif

