#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "inFormatters.hpp"

std::istream &arakelyan::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterIO;
  using lab = LableIO;
  using oct = OctUll;
  using ch = CharLit;
  using st = StringIO;
  in >> del{'('};
  in >> del{':'} >> lab{"key1"} >> oct{data.key1} >> del{':'};
  in >> lab{"key2"} >> ch{data.key2} >> del{':'};
  in >> lab{"key3"} >> st{data.key3} >> del{':'};
  in >> del{')'};
  return in;
}

std::ostream &arakelyan::operator<<(std::ostream &out, DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 0" << data.key1 << ":key2 '" << data.key2 << "':key3 \"" << data.key3 << "\":)";
  return out;
}
