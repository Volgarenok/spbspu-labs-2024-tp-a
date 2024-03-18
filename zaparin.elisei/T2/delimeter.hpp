#ifndef DELIMETER
#define DELIMETER

#include<istream>

namespace zaparin
{
  struct Delimeter
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, Delimeter&& exp);
}

#endif

