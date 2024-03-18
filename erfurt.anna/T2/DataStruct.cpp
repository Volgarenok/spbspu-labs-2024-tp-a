#include "DataStruct.hpp"
#include "Delimeter.hpp"

std::istream &erfurt::operator>>(std::istream &in, DataStruct &value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeter;

  in >> del{ "(:" };

  long long key11 = 0;
  unsigned long long key22 = 0;
  std::string key33 = "";
  size_t keyIndex = 0;

  for (int i = 0; i < 3 && in; ++i)
  {
    in >> del{ "key" } >> keyIndex;
    switch (keyIndex)
    {
    case 1:
      in >> key11 >> del{ "ll" };
      break;
    case 2:
      in >> key22 >> del{ "ull" };
      break;
    case 3:
      in >> del{ "\"" };
      std::getline(in, key33,'"');
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> del{ ":)" };
  if (in)
  {
    value = DataStruct{ key11, key22, key33 };
  }
  return in;
}
