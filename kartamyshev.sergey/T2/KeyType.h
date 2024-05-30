#ifndef KEYTYPE_H
#define KEYTYPE_H

#include <istream>
#include <string>

namespace kartamyshev
{
  struct DoubleKey
  {
    double& num;
  };
  std::istream& operator>>(std::istream& in, DoubleKey&& key);

  struct DoubleKeyOut
  {
    double num;
  };

  std::ostream& operator<<(std::ostream& out, const DoubleKeyOut&& key);

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


