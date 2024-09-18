#ifndef KEY_I_HPP
#define KEY_I_HPP

#include <istream>
#include <utility>
#include <string>

namespace kuzmina
{
  struct SLLKey
  {
    long long& value;
  };

  struct RATKey
  {
    std::pair< long long, unsigned long long >& value;
  };

  struct STRKey
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream&, SLLKey&&);
  std::istream& operator>>(std::istream&, RATKey&&);
  std::istream& operator>>(std::istream&, STRKey&&);
}

#endif
