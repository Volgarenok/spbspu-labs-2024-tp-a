#include "inputkey.hpp"
#include "delimeter.hpp"

void piyavkin::inputKey(std::istream& in, size_t numberKey, DataStruct& data)
{
  using dc = DelimeterChar;
  using ds = DelimeterString;
  if (numberKey == 1)
  {
    unsigned long long hex = 0;
    in >> std::hex >> hex >> std::dec >> ds{"ull"};
    if (in)
    {
      data.key1 = hex;
    }
  }
  else if (numberKey == 2)
  {
    long long int num = 0;
    unsigned long long den = 0;
    in >> ds{"(:n"} >> num >> ds{":d"} >> den >> ds{":)"};
    if (in)
    {
      data.key2.first = num;
      data.key2.second = den;
    }
  }
  else if (numberKey == 3)
  {
    std::string str = "";
    in >> dc{ '"' };
    std::getline(in, str, '"');
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