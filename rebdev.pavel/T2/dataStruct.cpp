#include "dataStruct.hpp"

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::DataStruct::operator<(const DataStruct & rhs) const
{
  if (key1_ == rhs.key1_)
  {
    if (key2_ == rhs.key2_)
    {
      return key3_ < rhs.key3_;
    }
    return (key2_ < rhs.key2_);
  }
  return (key1_ < rhs.key1_);
}

std::istream & rebdev::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry sentryGuard(in);
  if(!sentryGuard)  return in;
  StreamGuard guard(in);

  if (!(in >> delimeter_t{'('} >> delimeter_t{':'}))  return in;

  for (size_t i = 0; i < 3; ++i)
  {
    char num = 0;
    in >> delimeter_t{'k'} >> delimeter_t{'e'} >> delimeter_t{'y'} >> num;

    switch (num)
    {
      case '1':
        in >> data.key1_;
        break;

      case '2':
        in >> data.key2_;
        break;

      case '3':
        in >> data.key3_;
        break;

      default:
        return in;
    }

    if (!(in >> delimeter_t{':'}))  return in;

  }

  in >> delimeter_t{')'};
  return in;
}
std::ostream & rebdev::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard)  return out;
  StreamGuard guard(out);

  out << "(:key1 " << data.key1_;
  out << ":key2 " << data.key2_;
  out << ":key3 " << data.key3_ << ":)";

  return out;
}
