#include "dataStruct.hpp"

#include "delimiter.hpp"
#include "formatGuard.hpp"
#include "inFormatters.hpp"

bool arakelyan::operator<(const DataStruct &leftObj, const DataStruct &rightObj)
{
  if (leftObj.key1 == rightObj.key1)
  {
    if (leftObj.key2 == rightObj.key2)
    {
      return leftObj.key3.size() < rightObj.key3.size();
    }
    else
    {
      return leftObj.key2 < rightObj.key2;
    }
  }
  return leftObj.key1 < rightObj.key1;
}

std::istream &arakelyan::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterIO;
  using ull = OctUllIO;
  using ch = CharLitIO;
  using st = StringIO;
  size_t keysCounter = 0;
  in >> del{'('};
  while (in && (keysCounter != 3))
  {
    std::string tempKeyDef = "";
    in >> del{':'};
    in >> tempKeyDef;
    if ((tempKeyDef == "key1") && (keysCounter != 3))
    {
      in >> ull{data.key1};
      ++keysCounter;
    }
    else if ((tempKeyDef == "key2") && (keysCounter != 3))
    {
      in >> ch{data.key2};
      ++keysCounter;
    }
    else if ((tempKeyDef == "key3") && (keysCounter != 3))
    {
      in >> st{data.key3};
      ++keysCounter;
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
  FormatGuard formatGuard(out);
  out << "(";
  out << ":key1 0" << std::oct << data.key1;
  out << ":key2 '" << data.key2 << "'";
  out << ":key3 \"" << data.key3 << "\"";
  out << ":)";
  return out;
}
