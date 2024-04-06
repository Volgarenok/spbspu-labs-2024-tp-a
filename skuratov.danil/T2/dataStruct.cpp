#include "dataStruct.hpp"
#include "delimiter.hpp"

bool skuratov::DataStruct::operator<(const DataStruct& diff) const
{
  return (key1 != diff.key1) ? (key1 < diff.key1) : ((key2 != diff.key2) ? (key2 < diff.key2) : (key3 < diff.key3));
}

std::istream& skuratov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  in >> del{ '(' };
  while (true) {
    std::string field;
    in >> field;
    if (field == ":key1") {
      in >> del{ ' ' } >> value.key1 >> del{ ':' };
    }
    else if (field == ":key2") {
      in >> del{ ' ' } >> value.key2 >> del{ ':' };
    }
    else if (field == ":key3") {
      in >> del{ ' ' } >> value.key3 >> del{ ':' };
    }
    else if (field == ")") {
      break;
    }
  }
  return in;
}

std::ostream& skuratov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << value.key1 << ":key2 " << value.key2 << ":key3 " << value.key3 << ":)" << "\n";
  return out;
}
