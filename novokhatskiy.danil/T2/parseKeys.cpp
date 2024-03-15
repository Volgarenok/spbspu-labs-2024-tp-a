#include "parseKeys.hpp"
#include "delimiter.hpp"

std::istream &novokhatskiy::operator>>(std::istream &in, UnsignedLLKey &&tmp)
{
  using sDel = StringDelimiterI;
  std::istream::sentry shield(in);
  if (!shield)
  {
    return in;
  }
  unsigned long long value = 0;
  in >> sDel{"0b", true} >> value;
  if (in)
  {
    tmp.key1 = value;
  }
  return in;
}

std::istream &novokhatskiy::operator>>(std::istream &in, PairKey &&tmp)
{
  std::istream::sentry shield(in);
  if (!shield)
  {
    return in;
  }
  using cDel = DelimiterI;
  using sDel = StringDelimiterI;
  long long keyTmp1 = 0;
  unsigned long long keyTmp2 = 0;
  in >> sDel{":n ", true} >> keyTmp1 >> sDel{":d ", true} >> keyTmp2 >> sDel{":)"};
  if (in)
  {
    tmp.key2.first = keyTmp1;
    tmp.key2.second = keyTmp2;
  }
  return in;
}

std::istream &novokhatskiy::operator>>(std::istream &in, StringKey &&tmp)
{
  std::istream::sentry shield(in);
  if (!shield)
  {
    return in;
  }
  using cDel = DelimiterI;
  std::string s = "";
  in >> cDel{'"'};
  std::getline(in, s, '"');
  if (in)
  {
    tmp.key3 = s;
  }
  return in;
}
