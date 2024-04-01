#include "dataStruct.hpp"
#include "delimiter.hpp"

std::istream &arakelyan::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using sep = SeparIO;
  using lab = LableIO;
  int a = 0;
  int b = 0;
  in >> sep{'('};
  in >> lab{":key1"} >> a;
  in >> lab{":key2"} >> b;
  in >> sep{')'};
  if (in)
  {
    data = DataStruct(a,b);
  }
  return in;
}

std::ostream &arakelyan::operator<<(std::ostream &out, DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << ":key1 " << data.key1 << " :key2 " << data.key2 << ")";
  return out;
}
