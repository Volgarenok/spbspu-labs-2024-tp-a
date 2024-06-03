#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP
#include <iostream>
#include <string>
namespace sakovskaia
{
  struct UllBin
  {
    unsigned long long & num;
  };
  std::istream & operator>>(std::istream & input, UllBin && key);
  struct ChrLit
  {
    char & num;
  };
  std::istream & operator>>(std::istream & input, ChrLit && key);
  struct StrKey
  {
    std::string & str;
  };
  std::istream & operator>>(std::istream & input, StrKey && key);
}
#endif
