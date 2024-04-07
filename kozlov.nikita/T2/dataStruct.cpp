#include "dataStruct.hpp"
#include "inputCheck.hpp"
#include "dataFormats.hpp"
#include "streamGuard.hpp"

std::istream& kozlov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  using lab = Label;
  DataStruct temp{0, 0, ""};
  const int KEY_COUNT = 3;
  in >> del{'('};
  for (int i = 0; i < KEY_COUNT; i++)
  {
    int keyNum = 0;
    in >> lab{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> UllHexVal{temp.key1};
    }
    else if (keyNum == 2)
    {
      in >> ChrLitVal{temp.key2};
    }
    else if (keyNum == 3)
    {
      in >> StringVal{temp.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> lab{":)"};
  data = temp;
  return in;
}

std::ostream& kozlov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard streamGuard(out);
  out << '(';
  out << ":key1 0x" << std::hex << std::uppercase << data.key1;
  out << ":key2 \'" << data.key2 << '\'';
  out << ":key3 \"" << data.key3 << '"';
  out << ":)";
  return out;
}

bool kozlov::operator<(const DataStruct& left, const DataStruct& right)
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }
  if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }
  return left.key3.size() < right.key3.size();
}
