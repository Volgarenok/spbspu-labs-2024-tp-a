#include "dataStruct.hpp"

#include <iomanip>
#include <iostream>

#include "inputData.hpp"
#include "ioFormatGuard.hpp"

namespace zhalilov
{
  std::istream &inputKey(std::istream &in, DataStruct &data)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }
    std::string tmp;
    in >> tmp;
    if (tmp == "key1")
    {
      in >> DoubleSciI{ data.key1 };
    }
    else if (tmp == "key2")
    {
      in >> LongLongI{ data.key2 };
    }
    else
    {
      in >> StringI{ data.key3 };
    }
    return in;
  }

  std::ostream &outputScientific(std::ostream &out, double num)
  {
    ioFormatGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    int exp = 0;
    char sign = 0;
    if (num >= 1.0)
    {
      while (num > 1.0)
      {
        num /= 10;
        exp++;
      }
      sign = '+';
    }
    else
    {
      while (num < 1.0)
      {
        num *= 10;
        exp++;
      }
      sign = '-';
    }
    out << num << 'e' << sign << exp;
    return out;
  }
}

bool zhalilov::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < other.key3.size();
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}

bool zhalilov::DataStruct::operator>(const DataStruct &other) const
{
  return other < *this;
}

bool zhalilov::DataStruct::operator==(const DataStruct &other) const
{
  return key1 == other.key1 && key2 == other.key2 && key3 == other.key3;
}

bool zhalilov::DataStruct::operator<=(const DataStruct &other) const
{
  return !(other > *this);
}

bool zhalilov::DataStruct::operator>=(const DataStruct &other) const
{
  return !(*this < other);
}

std::istream &zhalilov::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  DataStruct input;
  in >> DelimiterI{ '(' } >> DelimiterI{ ':' };
  inputKey(in, input) >> DelimiterI{ ':' };
  inputKey(in, input) >> DelimiterI{ ':' };
  inputKey(in, input);
  in >> DelimiterI{ ':' } >> DelimiterI{ ')' };
  if (in)
  {
    data = input;
  }
  return in;
}

std::ostream &zhalilov::operator<<(std::ostream &out, const DataStruct &data)
{
  out << "(:key1 ";
  outputScientific(out, data.key1);
  out << ":key2 " << data.key2 << "ll";
  out << ":key3 ";
  out << std::quoted(data.key3);
  out << ":)";
  return out;
}
