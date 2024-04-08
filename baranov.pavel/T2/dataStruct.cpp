#include "dataStruct.hpp"
#include <string>
#include "delimiter.hpp"

std::istream& baranov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' };
  DataStruct input{0, std::complex< double >(0, 0), ""};
  for (size_t i = 0; i < 3; ++i)
  {
    std::string label;
    in >> LabelIO{ label };
    if (label == "key1")
    {
      in >> HexUllIO{ input.key1 };
    }
    else if (label == "key2")
    {
      in >> ComplexIO{ input.key2 };
    }
    else if (label == "key3")
    {
      in >> StringIO{ input.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  data = input;
  return in;
}

