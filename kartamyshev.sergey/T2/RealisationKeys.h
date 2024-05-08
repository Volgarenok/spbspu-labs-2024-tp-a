#ifndef REALISATIONKEYS_H
#define REALISATIONKEYS_H

#include <istream>
#include <string>

namespace kartamyshev
{
  struct DoubleKey
  {
    double& num;
  };
  std::istream& operator>>(std::istream& in, DoubleKey&& key);

  std::ostream& print(std::ostream& out, double num);

  struct LLKey
  {
    long long& num;
  };
  std::istream& operator>>(std::istream& in, LLKey&& key);

  struct StrKey
  {
    std::string& string;
  };
  std::istream& operator>>(std::istream& in, StrKey&& key);
}

#endif


