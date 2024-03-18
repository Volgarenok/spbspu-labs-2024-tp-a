#include "data_struct.hpp"
#include "delimeters.hpp"

namestnikov::DataStruct::DataStruct():
  key1(0.0),
  key2(0),
  key3("")
{}

namestnikov::DataStruct::DataStruct(double key1, unsigned long long key2, std::string key3):
  key1(key1),
  key2(key2),
  key3(key3)
{}

double namestnikov::DataStruct::getKey1() const
{
  return key1;
}

unsigned long long namestnikov::DataStruct::getKey2() const
{
  return key2;
}

std::string namestnikov::DataStruct::getKey3() const
{
  return key3;
}

bool namestnikov::DataStruct::operator<(const DataStruct & data) const
{
  if (key1 == data.key1)
  {
    if (key2 == data.key2)
    {
      return key3.length() < data.key3.length();
    }
    return key2 < data.key2;
  }
  return key1 < data.key1;
}

std::istream & namestnikov::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delC = DelimeterChar;
  using delS = DelimeterString;
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = "";
  const size_t MAX_LEN_KEYS = 3;
  size_t keyNumber = 0;
  in >> delC{'('};
  for (size_t i = 0; i < MAX_LEN_KEYS; ++i)
  {
    in >> delS{":key"} >> keyNumber;
    if (keyNumber == 1)
    {
      in >> key1 >> delC{'d'};
    }
    else if (keyNumber == 2)
    {
      in >> delC{'0'} >> std::oct >> key2 >> std::dec;
    }
    else if (keyNumber == 3)
    {
      in >> delC{'\"'} >> key3;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  if (in)
  {
    data = DataStruct(key1, key2, key3);
  }
  in >> delS{":)"};
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << data.getKey1() << "d";
  out << ":key2 " << "0" << data.getKey2();
  out << ":key3 " << "\"" << data.getKey3() << "\"" << ":)";
  return out;
}

std::istream & namestnikov::operator>>(std::istream & in, std::string & s)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char sym = 0;
  in >> std::noskipws;
  while ((in >> sym) && (sym != '\"'))
  {
    s += sym;
  }
  in >> std::skipws;
  return in;
}
