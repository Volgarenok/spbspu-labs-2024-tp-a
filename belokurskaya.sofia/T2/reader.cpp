#include "reader.hpp"

#include <sstream>
#include <iomanip>
#include <execution>

#include "streamGuard.hpp"


std::istream& operator>>(std::istream& in, DataStruct& dest)
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
        in >> sep{ '\'' } >> chr{input.key1} >> sep{ '\'' };
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

std::istream& operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, CharI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
}

std::istream& operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, StringKeyI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in, dest.ref, ' ');
}

std::istream& operator>>(std::istream& in, LongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  long long num = 0;
  in >> num;
  if (in)
  {
    dest.num = num;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& operator>>(std::istream& in, UnsignedLongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  unsigned long long num = 0;
  in >> num;
  if (in)
  {
    dest.num = num;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
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
