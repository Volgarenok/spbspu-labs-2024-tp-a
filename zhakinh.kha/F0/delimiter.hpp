#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace zhakha
{
  //struct Delimiter
  //{
  //  char expected;
  //};
  //std::istream& operator>>(std::istream& in, Delimiter&& exp);

  //struct DelimiterChar
  //{
  //  char expected;
  //};
  //std::istream& operator>>(std::istream& is, DelimiterChar&& exp)

  ///*{
  //  char ch;
  //  is >> ch;
  //  if (ch != exp.expected)
  //  {
  //    is.setstate(std::ios::failbit);
  //  }
  //  return is;
  //}*/

  //struct DelimiterAlphaChar
  //{
  //  char expected;
  //};
  //std::istream& operator>>(std::istream& in, DelimiterAlphaChar&& exp);

  //struct DelimiterString
  //{
  //  const char* expected;
  //};
  //std::istream& operator>>(std::istream& in, DelimiterString&& exp);

  struct DelimiterString
  {
    const char* expected;
  };
  struct DelimiterChar
  {
    char expected;
  };
  struct DelimiterIsAlpha
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
  std::istream& operator>>(std::istream& in, DelimiterString&& exp);
  std::istream& operator>>(std::istream& in, DelimiterIsAlpha&& exp);

}
#endif
