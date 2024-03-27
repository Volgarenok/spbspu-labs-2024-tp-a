#include "dataStruct.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::dataStruct_t::operator < (const dataStruct_t & rhv) const
{
  if (key1_.data_ == rhv.key1_.data_)
  {
    if (key2_.data_ == rhv.key2_.data_)
    {
      return key3_ < rhv.key3_;
    }
    return (key2_.data_ < rhv.key2_.data_);
  }
  return (key1_.data_ < rhv.key1_.data_);
}
bool rebdev::dataStruct_t::operator > (const dataStruct_t & rhv) const
{
  return (rhv < *this);
}

std::istream & rebdev::operator >> (std::istream & in, dataStruct_t & data)
{
  data.key1_ = {0, 0, 2};
  data.key2_ = {0, 0, 16};
  data.key3_.clear();

  std::istream::sentry sentryGuard(in);
  if(!sentryGuard) return in;

  StreamGuard guard(in);

  if (!(in >> delimeter_t{'('} >> delimeter_t{':'})) return in;

  std::string inputString;
  for (size_t i = 0; i < 3; ++i)
  {
    in >> inputString;

    if (inputString == "key1")
    {
      in >> delimeter_t{'0'} >> delimeter_t{'b'} >> data.key1_;
    }
    else if (inputString == "key2")
    {
      in >> delimeter_t{'0'} >> delimeter_t{'x'} >> data.key2_;
    }
    else if (inputString == "key3")
    {
      in >> delimeter_t{'\"'};
      std::getline(in, data.key3_, '\"');
    }
    else
    {
      return in;
    }

    if (!(in >> delimeter_t{':'})) return in;

    inputString.clear();
  }

  in >> delimeter_t{')'};
  return in;
}
std::ostream & rebdev::operator << (std::ostream & out, const dataStruct_t & data)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard) return out;

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << "(:key1 0b" << data.key1_;
  out << ":key2 0x" << data.key2_;
  out << ":key3 \"" << data.key3_ << "\":)";

  return out;
}
