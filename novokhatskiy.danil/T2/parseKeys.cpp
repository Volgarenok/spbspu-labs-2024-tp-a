#include "parseKeys.hpp"
#include "delimiter.hpp"

std::istream &novokhatskiy::operator>>(std::istream &in, UnsignedLLKey &&tmp)
{
  using strAD = novokhatskiy::DelimiterAlphaString;
  std::istream::sentry shield(in);
  if (!shield)
  {
    return in;
  }
  unsigned long long value = 0;
  in >> strAD{"0b"} >> value;
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
  using strAD = novokhatskiy::DelimiterAlphaString;
  using strD = novokhatskiy::DelimiterString;
  long long keyTmp1 = 0;
  unsigned long long keyTmp2 = 0;
  in >> strAD{":n "} >> keyTmp1 >> strAD{":d "} >> keyTmp2 >> strD{":)"};
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
  using charD = novokhatskiy::Delimiter;
  std::string s = "";
  in >> charD{'"'};
  std::getline(in, s, '"');
  if (in)
  {
    tmp.key3 = s;
  }
  return in;
}