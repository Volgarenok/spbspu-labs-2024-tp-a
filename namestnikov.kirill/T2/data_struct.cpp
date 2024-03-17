#include "data_struct.hpp"
#include "delimeters.hpp"

namestnikov::DataStruct::DataStruct(double key1, unsigned long long key2, std::string key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{}

double namestnikov::DataStruct::get_key1() const
{
  return key1_;
}

unsigned long long namestnikov::DataStruct::get_key2() const
{
  return key2_;
}

std::string namestnikov::DataStruct::get_key3() const
{
  return key3_;
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
  in >> delC{'['} >> key1 >> delC{'u'} >> key2 >> delS{"ull"} >> key3 >> delC{']'};
  if (in)
  {
    data = DataStruct(key1, key2, key3);
  }
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "[" << data.get_key1() << ";" << data.get_key2() << ";" << data.get_key3() << "]";
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
  return in;
}