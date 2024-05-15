#ifndef VALUE_HPP
#define VALUE_HPP
#include <string>

namespace kozlova
{
  struct DblLitIO
  {
    double& key1;
  };

  struct RatLspFIO
  {
    long long& firstKey2;
  };

  struct RatLspSIO
  {
    unsigned long long& secondKey2;
  };

  struct StringIO
  {
    std::string& key3;
  };

  std::istream& operator>>(std::istream& in, DblLitIO&& dest);
  std::istream& operator>>(std::istream& in, RatLspFIO&& dest);
  std::istream& operator>>(std::istream& in, RatLspSIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}
#endif
