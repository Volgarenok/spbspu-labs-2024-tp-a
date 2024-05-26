#include "data_struct.hpp"
#include <string>
#include "stream_guard.hpp"
#include "delimiter_formats.hpp"

bool lopatina::operator<(const DataStruct & first, const DataStruct & second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  return first.key3.size() < second.key3.size();
}

std::istream & lopatina::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  DataStruct input;
  {
    using del = DelimiterIO;
    using str = StringIO;
    using ull_lit = UllLiteralIO;
    std::string key;
    in >> del{'('} >> del{':'};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> key;
      if (key == "key1")
      {
        in >> ull_lit{input.key1} >> del{':'};
      }
      else if (key == "key2")
      {
        in >> del{'('} >> del{':'} >> del{'n'};
        in >> input.key2.first;
        in >> del{':'} >> del{'d'};
        in >> input.key2.second;
        in >> del{':'} >> del{')'} >> del{':'};
      }
      else if (key == "key3")
      {
        in >> str{input.key3} >> del{':'};
      }
    }
    in >> del{')'};
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & lopatina::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  out << "(:key1 " << data.key1 << "ull";
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
