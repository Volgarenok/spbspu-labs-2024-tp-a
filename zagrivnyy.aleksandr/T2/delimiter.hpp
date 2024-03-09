#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace zagrivnyy
{
  struct DelimiterI
  {
    DelimiterI(const char *expected);

    const char *expected;

    size_t length()
    {
      return size;
    };

  private:
    size_t size;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&exp);

  struct AnyCaseDelimiterI: public DelimiterI
  {
    AnyCaseDelimiterI(const char *expected): DelimiterI(expected){};
  };

  std::istream &operator>>(std::istream &in, AnyCaseDelimiterI &&exp);

}     // namespace zagrivnyy

#endif
