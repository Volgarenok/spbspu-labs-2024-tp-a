#include "inputFunctions.hpp"
#include "delimeter.hpp"

void marishin::inputKeys(std::istream& in, size_t y, DataStruct& data)
{
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

void marishin::printScientific(std::string& dest, double value)
{
  char buffer[64]{};
  snprintf(buffer, sizeof(buffer), "%.1e", value);
  dest = buffer;

  size_t pos = dest.find('e');
  if (pos != std::string::npos)
  {
    pos += 2;
    if (dest[pos] == '0')
    {
      dest.erase(pos, 1);
    }
  }
}
