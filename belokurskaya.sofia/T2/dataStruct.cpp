#include "dataStruct.hpp"

#include "reader.hpp"
#include "streamGuard.hpp"

bool belokurskaya::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 < other.key1)
  {
    return true;
  }
  else if (key1 == other.key1)
  {
    if (key2 < other.key2)
    {
      return true;
    }
    else if (key2 == other.key2)
    {
      return key3 < other.key3;
    }
    return false;
  }
  return false;
}

std::istream& belokurskaya::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterI;
    using chr = CharI;
    using str = StringI;
    using strKey = StringKeyI;
    using LLNum = LongLongI;
    using ULLNum = UnsignedLongLongI;
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++)
    {
      std::string key;
      in >> sep{ ':' } >> strKey{ key };
      if (key == "key1")
      {
        in >> sep{ '\'' } >> chr{ input.key1 } >> sep{ '\'' };
      }
      else if (key == "key2")
      {
        long long int valueN = 0;
        unsigned long long int valueD = 0;
        in >> sep{ '(' } >> sep{ ':' } >> sep{ 'N' } >> LLNum{ valueN };
        input.key2.first = valueN;
        in >> sep{ ':' } >> sep{ 'D' } >> ULLNum{ valueD };
        input.key2.second = valueD;
        in >> sep{ ':' } >> sep{ ')' };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
  }
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  dest = input;
  return in;
}

std::ostream& belokurskaya::operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << "(:";
  out << "key1 '" << dest.key1 << "':";
  out << "key2 (:N " << dest.key2.first << ":D " << dest.key2.second << ":):";
  out << "key3 \"" << dest.key3;
  out << "\":)";
  return out;
}
