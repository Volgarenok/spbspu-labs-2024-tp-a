#include "datastruct.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include "streamguard.hpp"
#include "delimiters.hpp"
#include "key_input.hpp"

bool prisyach::DataStruct::operator<(const DataStruct & data) const
{
  if (firstKey == data.firstKey)
  {
    if (secondKey == data.secondKey)
    {
      return thirdKey.length() < data.thirdKey.length();
    }
    else
    {
      return secondKey < data.secondKey;
    }
  }
  else
  {
    return firstKey < data.firstKey;
  }
}

std::istream & prisyach::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    StreamGuard streamGuard(in);
    in >> DelimiterChar{'('};
    int tries = 3;
    while (tries > 0)
    {
      size_t keyNumber = 0;
      in >> DelimiterString{":key"} >> keyNumber;
      if (keyNumber == 1)
      {
        in >> FirstKey{data.firstKey};
      }
      else if (keyNumber == 2)
      {
        in >> SecondKey{data.secondKey};
      }
      else if (keyNumber == 3)
      {
        in >> ThirdKey{data.thirdKey};
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      --tries;
    }
    in >> DelimiterString{":)"};
    return in;
  }
}

std::ostream & prisyach::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  else
  {
    out << std::fixed << std::setprecision(1);
    out << "(:key1 ";
    double num = data.firstKey;
    unsigned int power = 0;
    char sign = '+';
    if (std::abs(num) >= 10.0)
    {
      while (std::abs(num) >= 10.0)
      {
        num /= 10;
        ++power;
      }
    }
    else if (std::abs(num) < 1.0)
    {
      while (std::abs(num) < 1.0)
      {
        num *= 10;
        ++power;
      }
      sign = '-';
    }
    out << num << "e" << sign << power;
    out << std::oct;
    out << ":key2 " << "0" << data.secondKey;
    out << ":key3 \"" << data.thirdKey << "\":)";
    return out;
  }
}
