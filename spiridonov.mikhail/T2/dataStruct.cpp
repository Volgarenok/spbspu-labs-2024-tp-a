#include "dataStruct.hpp"
#include "delimeter.hpp"
#include <iomanip>

std::istream& spiridonov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    using delc = DelimeterChar;
    using dels = DelimeterString;
    in >> delc{ '(' };
    size_t key = 0;
    for (size_t i = 0; i < 3 && in; i++)
    {
      in >> dels{ ":key" } >> key;
      if (key == 1)
      {
        double temp = 0;
        in >> temp;
        if (in)
        {
          value.key1 = temp;
        }
      }
      else if (key == 2)
      {
        unsigned long long temp = 0;
        in >> temp >> dels{ "ull" };
        if (in)
        {
          value.key2 = temp;
        }
      }
      else if (key == 3)
      {
        std::string str = "";
        in >> str;
        if (in)
        {
          value.key3 = str;
        }
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> dels{ ":)" };
  }
  return in;
}

std::istream& spiridonov::operator>>(std::istream& in, std::string& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    in >> DelimeterChar{ '"' };
    std::getline(in, exp, '"');
  }
  return in;
}

std::ostream& outScientific(std::ostream& out, double number)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  int exp = 0;
  char sign = 0;
  if (number != 0)
  {
    if (number >= 1.0)
    {
      while (number > 1.0)
      {
        number = number / 10;
        exp++;
      }
      sign = '+';
    }
    else
    {
      while (number < 1.0)
      {
        number = number * 10;
        exp++;
      }
      sign = '-';
    }
    out << number << 'e' << sign << exp;
  }
  else
  {
    out << number;
  }
  return out;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << "(:key1 ";
    outScientific(out, value.key1);
    out << ":key2 " << value.key2 << "ull";
    out << ":key3 " << '"' << value.key3 << '"' << ":)";
  }
  return out;
}

bool spiridonov::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 != data.key1)
  {
    return key1 < data.key1;
  }
  if (key2 != data.key2)
  {
    return key2 < data.key2;
  }
  return key3.length() < data.key3.length();
}