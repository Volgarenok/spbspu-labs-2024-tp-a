#ifndef INPUTDATADETAIL_HPP
#define INPUTDATADETAIL_HPP

#include <iosfwd>

namespace zhalilov
{
  struct DelimiterI
  {
    char expected;
  };

  struct DoubleSciI
  {
    double &num;
  };

  struct MantissI
  {
    double &num;
  };

  struct LongLongI
  {
    long long &num;
  };

  struct StringI
  {
    std::string &text;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&symb);
  std::istream &operator>>(std::istream &in, DoubleSciI &&dbl);
  std::istream &operator>>(std::istream &in, MantissI &&mantiss);
  std::istream &operator>>(std::istream &in, LongLongI &&ll);
  std::istream &operator>>(std::istream &in, StringI &&str);
}

#endif
