#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace ayupov{
  struct DelimiterChar{
    char expected;
  };
  struct DblSciI{
    double& num;
  };
  struct MantissaI{
    double& mantissa;
  };
  struct StringI{
    std::string text;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
  std::istream& operator>>(std::istream& in, DblSciI&& dbl);
  std::istream& operator>>(std::istream& in, MantissaI&& mantissa);
  std::istream& operator>>(std::istream& in, StringI&& str);
}

#endif