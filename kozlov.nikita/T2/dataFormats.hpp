#ifndef DATA_FORMATS_HPP
#define DATA_FORMATS_HPP
#include <istream>

namespace kozlov
{
  struct UllHexVal
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, UllHexVal&& key);

  struct ChrLitVal
  {
    char& value;
  };
  std::istream& operator>>(std::istream& in, ChrLitVal&& key);

  struct StringVal
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StringVal&& key);
}
#endif
