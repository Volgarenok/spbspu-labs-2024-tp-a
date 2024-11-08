#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>
#include <ios>

namespace kumekova
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct& value) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);

  struct DelimiterString
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& exp);

  struct DelimiterChar
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };

  struct KeyHex
  {
    unsigned long long& value;
  };

  std::istream& operator>>(std::istream& in, KeyHex&& v);

  struct KeyLit
  {
    unsigned long long& value;
  };

  std::istream& operator>>(std::istream& in, KeyLit&& v);

  struct KeyString
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream& in, KeyString&& v);
}
#endif
