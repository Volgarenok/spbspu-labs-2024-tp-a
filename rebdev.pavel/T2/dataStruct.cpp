#include "dataStruct.hpp"

#include "delimeter.hpp"
#include "streamGuard.hpp"
#include "hexType.hpp"
#include "binType.hpp"
#include "stringType.hpp"

bool rebdev::DataStruct::operator<(const DataStruct & rhs) const
{
  if (key1_ == rhs.key1_)
  {
    if (key2_ == rhs.key2_)
    {
      return key3_.size() < rhs.key3_.size();
    }
    return (key2_ < rhs.key2_);
  }
  return (key1_ < rhs.key1_);
}

std::istream & rebdev::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry sentryGuard(in);
  if(!sentryGuard)
  {
    return in;
  }
  StreamGuard guard(in);

  if (!(in >> Delimeter{'('} >> Delimeter{':'}))
  {
    return in;
  }

  for (size_t i = 0; i < 3; ++i)
  {
    char num = 0;
    in >> Delimeter{'k'} >> Delimeter{'e'} >> Delimeter{'y'} >> num;

    switch (num)
    {
      case '1':
        in >> BinTypeIO{data.key1_};
        break;

      case '2':
        in >> HexTypeIO{data.key2_} >> Delimeter{':'};
        break;

      case '3':
        in >> StringTypeIO{data.key3_} >> Delimeter{':'};
        break;

      default:
        return in;
    }
  }

  in >> Delimeter{')'};
  return in;
}
std::ostream & rebdev::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard)
  {
    return out;
  }
  StreamGuard guard(out);

  DataStruct structCopy = data;

  out << "(:key1 " << BinTypeIO{structCopy.key1_};
  out << ":key2 " << HexTypeIO{structCopy.key2_};
  out << ":key3 " << StringTypeIO{structCopy.key3_} << ":)";

  return out;
}
