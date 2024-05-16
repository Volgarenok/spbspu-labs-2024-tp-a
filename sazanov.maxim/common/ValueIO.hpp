#ifndef VALUE_I_O_HPP
#define VALUE_I_O_HPP

#include <iosfwd>

namespace sazanov
{
  struct BinUllI
  {
    unsigned long long& number;
  };
  std::istream& operator>>(std::istream& in, BinUllI&& value);

  struct BinUllO
  {
    const unsigned long long& number;
  };
  std::ostream& operator<<(std::ostream& out, const BinUllO&& value);

  struct CharKeyI
  {
    char& ch;
  };
  std::istream& operator>>(std::istream& in, CharKeyI&& value);

  struct StringKeyI
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringKeyI&& value);
}

#endif
