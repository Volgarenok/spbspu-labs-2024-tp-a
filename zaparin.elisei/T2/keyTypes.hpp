#ifndef KEY_TYPES_HPP
#define KEY_TYPES_HPP

#include <istream>

namespace zaparin
{
  struct KeyType
  {
    size_t& value;
  };
  std::istream& operator>>(std::istream& in, KeyType&& exp);

  struct UllBin
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, UllBin&& exp);

  struct RatLsp
  {
    std::pair< long long, unsigned long long >& value;
  };
  std::istream& operator>>(std::istream& in, RatLsp&& exp);

  struct String
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, String&& exp);
}

#endif
