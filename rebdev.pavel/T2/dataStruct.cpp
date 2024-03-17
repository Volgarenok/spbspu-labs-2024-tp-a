#include "dataStruct.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"

std::istream & rebdev::operator >> (std::istream & in, dataStruct_t & data)
{
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
std::ostream & rebdev::operator << (std::ostream & out, dataStruct_t & data)
{
  StreamGuard guard(out);

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
