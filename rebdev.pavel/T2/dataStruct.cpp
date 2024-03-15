#include "dataStruct.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"

std::istream & rebdev::operator >> (std::istream & in, dataStruct & data)
{
  streamGuard guard(in);

  if (!(in >> delimeter{'('} >> delimeter{':'})) return in;

  std::string inputString;
  for (size_t i = 0; i < 3; ++i)
  {
    in >> inputString;

    if (inputString == "key1")
    {
      in >> delimeter{'0'} >> delimeter{'b'} >> data.key1_;
    }
    else if (inputString == "key2")
    {
      in >> delimeter{'0'} >> delimeter{'x'} >> data.key2_;
    }
    else if (inputString == "key3")
    {
      in >> delimeter{'\"'};
      std::getline(in, data.key3_, '\"');
    }
    else
    {
      return in;
    }

    if (!(in >> delimeter{':'})) return in;

    inputString.clear();
  }

  in >> delimeter{')'};
  return in;
}
std::ostream & rebdev::operator << (std::ostream & out, const dataStruct & data)
{
  streamGuard guard(out);

  std::ostream::sentry sentryGuard(out);
  if (sentryGuard)
  {
    out << std::setprecision(1) << std::fixed;
    out << "(:key1 0B" << data.key1_;
    out << ":key2 0X" << data.key2_;
    out << ":key3 \"" << data.key3_ << "\":)";
  }

  return out;
}
