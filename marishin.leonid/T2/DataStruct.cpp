#include "DataStruct.hpp"
#include "delimeter.hpp"
#include <iomanip>

std::istream& marishin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    using del = Delimeterchar;
    using dell = Delimeterstring;
    in >> del{ '(' };
    size_t keys = 3;
    size_t y = 0;
    for (size_t i = 0; i < keys; ++i)
    {
      in >> dell{ ":key" } >> y;
      using ds = Delimeterstring;
      if (y == 1)
      {
        double num1 = 0;
        in >> num1;
        if (in)
        {
          data.key1 = num1;
        }
      }
      else if (y == 2)
      {
        long long int num = 0;
        unsigned long long den = 0;
        in >> ds{ "(:n" } >> num >> ds{ ":d" } >> den >> ds{ ":)" };
        if (in)
        {
          data.key2.first = num;
          data.key2.second = den;
        }
      }
      else if (y == 3)
      {
        std::string str = "";
        in >> str;
        if (in)
        {
          data.key3 = str;
        }
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> dell{ ":)" };
  }
  return in;
}

std::istream& marishin::operator>>(std::istream& in, std::string& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    in >> Delimeterchar{ '"' };
    std::getline(in, exp, '"');
  }
  return in;
}

std::ostream& printScientific(std::ostream& out, double number)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  int exp = 0;
  char mark = 0;
  if (number != 0)
  {
    if (number >= 1.0)
    {
      while (number > 1.0)
      {
        number = number / 10;
        exp++;
      }
      mark = '+';
    }
    else
    {
      while (number < 1.0)
      {
        number = number * 10;
        exp++;
      }
      mark = '-';
    }
    out << number << 'e' << mark << exp;
  }
  else
  {
    out << number;
  }
  return out;
}

std::ostream& marishin::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << "(:key1 ";
    printScientific(out, value.key1);
    out << ":key2 (:N " << value.key2.first << ":D " << value.key2.second << ":)";
    out << ":key3 " << '"' << value.key3 << '"' << ":)";
  }
  return out;
}

bool marishin::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (key2.first * data.key2.second == key2.second * data.key2.first)
    {
      return key3 < data.key3;
    }
    return key2.first * data.key2.second < key2.second * data.key2.first;
  }
  return key1 < data.key1;
}

bool marishin::DataStruct::operator>=(const DataStruct& data) const
{
  return !(*this < data);
}

bool marishin::DataStruct::operator<=(const DataStruct& data) const
{
  return !(data < *this);
}

bool marishin::DataStruct::operator>(const DataStruct& data) const
{
  return (data < *this);
}

bool marishin::DataStruct::operator==(const DataStruct& data) const
{
  return !(*this < data) && !(data < *this);
}

bool marishin::DataStruct::operator!=(const DataStruct& data) const
{
  return !(data == *this);
}
