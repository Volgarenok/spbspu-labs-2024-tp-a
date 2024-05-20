#ifndef TOKENS_HPP
#define TOKENS_HPP
#include <string>

namespace zakozhurnikova
{
  struct DblLit
  {
    double& key1;
  };

  std::istream& operator>>(std::istream& in, DblLit&& data);

  struct UllHex
  {
    unsigned long long& key2;
  };

  std::istream& operator>>(std::istream& in, UllHex&& data);

  struct StringKey
  {
    std::string& key3;
  };

  std::istream& operator>>(std::istream& in, StringKey&& data);

}

#endif
