#include "data_struct.hpp"
#include "delimeters.hpp"

namestnikov::DataStruct::DataStruct():
  key1_(0.0),
  key2_(0),
  key3_("")
{}

namestnikov::DataStruct::DataStruct(double key1, unsigned long long key2, std::string key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{}

double namestnikov::DataStruct::getKey1() const
{
  return key1_;
}

unsigned long long namestnikov::DataStruct::getKey2() const
{
  return key2_;
}

std::string namestnikov::DataStruct::getKey3() const
{
  return key3_;
}

bool namestnikov::DataStruct::operator<(const DataStruct & data) const
{
  if (key1_ == data.key1_)
  {
    if (key2_ == data.key2_)
    {
      return key3_.length() < data.key3_.length();
    }
    return key2_ < data.key2_;
  }
  return key1_ < data.key1_;
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
