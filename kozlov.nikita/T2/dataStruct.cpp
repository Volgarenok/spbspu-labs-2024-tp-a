#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "dataFormats.hpp"
#include "streamGuard.hpp"

std::istream& kozlov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  using delChr = DelimiterChr;
  using delStr = DelimiterStr;
  DataStruct temp{0, 0, ""};
  int keyCount = 3;
  in >> delChr{'('};
  for (int i = 0; i < keyCount; i++)
  {
    int keyNum = 0;
    in >> delStr{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> UllHexVal{temp.key1};
    }
    if (keyNum == 2)
    {
      in >> ChrLitVal{temp.key2};
    }
    if (keyNum == 3)
    {
      in >> StringVal{temp.key3};
    }
  }
  in >> delStr{":)"};
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
