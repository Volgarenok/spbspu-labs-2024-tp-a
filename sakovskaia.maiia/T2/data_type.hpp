#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP
#include <iosfwd>
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
    char & chr_lit;
  };
  std::istream & operator>>(std::istream & input, ChrLit && key);
  struct StrKey
  {
    std::string & str;
  };
  std::istream & operator>>(std::istream & input, StrKey && key);
}
#endif
