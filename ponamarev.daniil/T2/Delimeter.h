#ifndef DELIMETER_H
#define DELIMETER_H

#include <string>
#include <iosfwd>

namespace ponamarev
{
  struct DataStruct;
  struct TypeIO
  {
    DataStruct& ref;
  };
  struct DelimeterIO
  {
    char exp;
  };
  struct UnsignedLongLongHexIO
  {
    unsigned long long& ref;
  };
  struct RationalIO
  {
    std::pair<long long, unsigned long long>& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DelimeterIO&& symb);
  std::istream& operator>>(std::istream& in, UnsignedLongLongHexIO&& ull);
  std::istream& operator>>(std::istream& in, RationalIO&& rat);
  std::istream& operator>>(std::istream& in, StringIO&& str);
  std::istream& operator>>(std::istream& in, DataStruct&& data);
  std::istream& operator>>(std::istream& in, LabelIO&& labe);
}

#endif
