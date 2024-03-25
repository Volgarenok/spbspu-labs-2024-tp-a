#include "DataStruct.h"

petrov::DataStruct::DataStruct(long long key1, unsigned long long key2, const std::string& key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{
}
bool petrov::DataStruct::operator<(const DataStruct& other) const
{
  if (!(key1_ == other.key1_))
  {
    return key1_ < other.key1_;
  }
  if (!(key2_ == other.key2_))
  {
    return key2_ < other.key2_;
  }
  return key3_.length() < other.key3_.length();
}
std::istream& petrov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input(dest);
  {
    using sep = DelimeterI;
    using ll = LongLongI;
    using label = LabelI;
    in >> sep{ '(' } >> label{"key"} >> ll{input.key1_};
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, LongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> dest.ref;
  std::string typeMarker = "";
  in >> typeMarker;
  if (in && ((typeMarker != "ll") && (typeMarker != "LL")))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, DelimeterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in.get(c);
  if (in && (c != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream & in, LabelI && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  in >> data;
  if (in && (data != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
