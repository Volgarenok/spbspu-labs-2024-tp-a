#ifndef INPUTDATADETAIL_HPP
#define INPUTDATADETAIL_HPP

#include <iosfwd>

namespace zhalilov
{
  struct DataStruct;

  namespace detail
  {
    struct DelimiterI
    {
      char expected;
    };

    struct DoubleI
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
    std::istream &operator>>(std::istream &in, DoubleI &&dbl);
    std::istream &operator>>(std::istream &in, LongLongI &&ll);
    std::istream &operator>>(std::istream &in, StringI &&str);

    std::istream &inputKey(std::istream &in, DataStruct &data);
  }
}

#endif
