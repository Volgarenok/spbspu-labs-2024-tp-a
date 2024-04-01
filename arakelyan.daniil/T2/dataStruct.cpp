#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "formatGuard.hpp"
#include "inFormatters.hpp"

bool arakelyan::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.length() < other.key3.length();
    }
    else
    {
      return key2 < other.key2;
    }
  }
  return key1 < other.key1;
}

std::istream &arakelyan::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterIO;
  // using lab = LableIO;
  using ull = OctUll;
  using ch = CharLit;
  using st = StringIO;
  int parCounter = 0;

  in >> del{'('};
  while (in && (parCounter != 3))
  {
    int tempKeyDef = 0;
    in >> del{':'};
    in >> del{'k'} >> del{'e'} >> del{'y'} >> tempKeyDef;
    if ((tempKeyDef == 1) && (parCounter != 3))
    {
      in >> ull{data.key1};
      ++parCounter;
    }
    else if ((tempKeyDef == 2) && (parCounter != 3))
    {
      in >> ch{data.key2};
      ++parCounter;
    }
    else if ((tempKeyDef == 3) && (parCounter != 3))
    {
      in >> st{data.key3};
      ++parCounter;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{':'} >> del{')'};
  return in;
}

std::ostream &arakelyan::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 0" << data.key1 << ":key2 '" << data.key2 << "':key3 \"" << data.key3 << "\":)";
  return out;
}
