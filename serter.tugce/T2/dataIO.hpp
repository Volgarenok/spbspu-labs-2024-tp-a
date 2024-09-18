#ifndef DATAIO_HPP
#define DATAIO_HPP

#include <string>

namespace serter
{
  struct StringIO
  {
    std::string& val;
  };

  struct DoubleIO
  {
    double& val;
  };

  struct UnsignedllIO
  {
    unsigned long long& val;
  };

  struct DelimiterIO
  {
    char val;
  };

  struct LabelIO
  {
    std::string val;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& val);
  std::istream& operator>>(std::istream& in, StringIO&& val);
  std::istream& operator>>(std::istream& in, DoubleIO&& val);
  std::istream& operator>>(std::istream& in, UnsignedllIO&& val);
  std::istream& operator>>(std::istream& in, LabelIO&& val);
  std::string fromDoubleToScientific(double val);
  std::string fromULLtoBinary(unsigned long long value);
}

#endif

