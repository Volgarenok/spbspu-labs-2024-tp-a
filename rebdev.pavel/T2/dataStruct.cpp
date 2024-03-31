#include "dataStruct.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"
#include "binFunction.hpp"

bool rebdev::DataStruct::operator<(const DataStruct & rhv) const
{
  if (key1_ == rhv.key1_)
  {
    if (key2_ == rhv.key2_)
    {
      return key3_ < rhv.key3_;
    }
    return (key2_ < rhv.key2_);
  }
  return (key1_ < rhv.key1_);
}

bool rebdev::DataStruct::operator>(const DataStruct & rhv) const
{
  return (rhv < *this);
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
        in >> delimeter_t{'0'} >> delimeter_t{'b'};
        data.key1_ = inputBin(in);
        break;

      case '2':
        in >> delimeter_t{'0'} >> delimeter_t{'x'} >> std::hex >> data.key2_;
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
  if (!sentryGuard) return out;
  StreamGuard guard(out);

  out << "(:key1 0b";
  outputBin(out, data.key1_);
  out << ":key2 0x" << std::showbase << std::uppercase << std::hex << data.key2_ << std::noshowbase;
  out << ":key3 \"" << data.key3_ << "\":)";

  return out;
}

std::istream & rebdev::operator>>(std::istream & in, std::string & str)
{
  in >> delimeter_t{'\"'};
  std::getline(in, str, '\"');
  return in;
}
