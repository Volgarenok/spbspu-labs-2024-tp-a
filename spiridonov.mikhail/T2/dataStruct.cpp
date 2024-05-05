#include <istream>
#include <ostream>
#include <string>
#include <iomanip>
#include "dataStruct.hpp"
#include "delimeter.hpp"
#include "key.hpp"

std::istream& spiridonov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimeterChar{'('};
  int keyNum = 0;
  for (int i = 0; i < 3; i++)
  {
    in >> DelimeterString{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> DblSciI{data.key1};
    }
    else if (keyNum == 2)
    {
      in >> UllLiteralIO{data.key2};
    }
    else if (keyNum == 3)
    {
      in >> StringI{data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimeterString{":)"};
  return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 ";
  double dblSci = data.key1;
  char sigh = 0;
  int power = 0;
  while (dblSci >= 10)
  {
    dblSci /= 10;
    power++;
  }
  while (dblSci < 1)
  {
    dblSci *= 10;
    power--;
  }
  if (power < 0)
  {
    sigh = '-';
  }
  else if (power > 0)
  {
    sigh = '+';
  }
  
  
  if (guard)
  {  
  out << std::fixed << std::setprecision(1) << dblSci << 'e' << sigh << std::abs(power);
  out << ":key2 '" << data.key2 << '\'';
  out << ":key3 \"" << data.key3 << "\":)";
  }
  return out;
}

bool spiridonov::DataStruct::operator<(const DataStruct& anotherData) const
{
  if (key1 == anotherData.key1)
  {
    if (key2 == anotherData.key2)
    {
      return key3.size() < key3.size();
    }
    return key2 < anotherData.key2;
  }
  return key1 < anotherData.key1;
}