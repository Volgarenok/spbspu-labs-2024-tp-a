#ifndef FORMATS_HPP
#define FORMATS_HPP
#include <istream>

namespace timchishina
{
  struct SllLit
  {
    long long & key;
  };
  std::istream & operator>>(std::istream & in, SllLit && data);

  struct UllOct
  {
    unsigned long long & key;
  };
  std::istream & operator>>(std::istream& in, UllOct  && data);

  struct StringKey
  {
    std::string & key;
  };
  std::istream & operator>>(std::istream & in, StringKey && data);
}
#endif
