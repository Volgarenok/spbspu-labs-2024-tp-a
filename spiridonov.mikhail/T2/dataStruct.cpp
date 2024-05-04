#include <istream>
#include <ostream>
#include <string>
#include <iomanip>
#include "dataStruct.hpp"
#include "delimeter.hpp"

std::istream& spiridonov::operator>>(std::istream& in, DataStruct& value)
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
      in >> DblSciI{value.key1};
    }
    else if (keyNum == 2)
    {
      in >> UllLiteralIO{value.key2};
    }
    else if (keyNum == 3)
    {
      in >> StringI{value.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimeterString{":)"};
  return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 ";
  double dblSci = value.key1;
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
  out << std::fixed << std::setprecision(1) << dblSci << 'e' << sigh << std::abs(power);
  out << ":key2 '" << value.key2 << '\'';
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

bool spiridonov::operator<(const DataStruct& firstData, const DataStruct& secondData)
{
  if (firstData.key1 == secondData.key1)
  {
    if (firstData.key2 == secondData.key2)
    {
      return firstData.key3.size() < secondData.key3.size();
    }
    return firstData.key2 < secondData.key2;
  }
  return firstData.key1 < secondData.key1;
}
