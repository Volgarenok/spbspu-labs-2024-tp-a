#include "dataStruct.hpp"
#include "delimiter.hpp"
#include <iomanip>

bool demin::DataStruct::operator<(const DataStruct &src) const
{
  if (key1 == src.key1)
  {
    if (key2 == src.key2)
    {
      return key3.length() < src.key3.length();
    }
    return key2 < src.key2;
  }
  return key1 < src.key1;
}

std::istream &demin::operator>>(std::istream &in, DataStruct &data)
{
  using del = demin::DelimiterI;

  in >> del{"("};

  double dbl = .0;
  unsigned long long int oct = 0;
  std::string str = "";

  const size_t KEYS_COUNT = 3;
  for (size_t i = 0; i < KEYS_COUNT; ++i)
  {
    size_t key = 0;
    in >> del{":key"} >> key;

    if (key == 1)
    {
      demin::parse(in, dbl);
    }
    else if (key == 2)
    {
      demin::parse(in, oct);
    }
    else if (key == 3)
    {
      demin::parse(in, str);
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> del{":)"};

  if (in)
  {
    data.key1 = dbl;
    data.key2 = oct;
    data.key3 = str;
  }

  return in;
}

std::ostream &demin::operator<<(std::ostream &out, const DataStruct &data)
{
  out << "(:key1 " << std::setprecision(1) << std::fixed << data.key1 << "d";
  out << ":key2 0" << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";

  return out;
}

void demin::parse(std::istream &in, double &src)
{
  double dbl = .0;

  using iDel = demin::InsensetiveDelimiterI;
  in >> dbl >> iDel{"d"};

  if (in)
  {
    src = dbl;
  }
}

void demin::parse(std::istream &in, unsigned long long &src)
{
  using del = demin::DelimiterI;

  unsigned long long oct = 0;
  in >> del{"0"} >> oct;

  if (in)
  {
    src = oct;
  }
}

void demin::parse(std::istream &in, std::string &src)
{
  std::string str = "";

  using del = demin::DelimiterI;
  in >> del{"\""};
  std::getline(in, str, '"');

  if (in)
  {
    src = str;
  }
}
