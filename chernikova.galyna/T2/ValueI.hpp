#ifndef VALUEI_HPP
#define VALUEI_HPP

#include <istream>
#include <string>

namespace chernikova
{
  struct DoubleI
  {
    double& ref;
  };

  struct UnsignedllI
  {
    unsigned long long& ref;
  };

  struct StringI
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DoubleI&& exp);
  std::istream& operator>>(std::istream& in, UnsignedllI&& exp);
  std::istream& operator>>(std::istream& in, StringI&& dest);
  std::string convertDblToSci(double num);
}

#endif
