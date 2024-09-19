#ifndef VALUE_HPP
#define VALUE_HPP

#include <delimeter.hpp>

namespace marishin
{
  struct DblSci
  {
    double& value;
  };
  struct DoubleSci
  {
    double value;
  };
  struct StringStr
  {
    std::string& value;
  };
  struct RatLsp
  {
    std::pair< long long, unsigned long long >& value;
  };
  std::istream& operator>>(std::istream& in, DblSci&& value);
  std::ostream& operator<<(std::ostream& out, const DoubleSci&& value);
  std::istream& operator>>(std::istream& in, StringStr&& value);
  std::istream& operator>>(std::istream& in, RatLsp&& value);
}

#endif
