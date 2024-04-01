#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& kozlov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  using delCh = DelimiterCh;
  using delStr = DelimiterStr;
  DataStruct temp{0, 0, ""};
  int keyCount = 3;
  in >> delCh{'('};
  for (int i = 0; i < keyCount; i++)
  {
    int keyNum = 0;
    in >> delStr{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> std::hex;
      in >> delStr{"0x"} >> temp.key1;
    }
    if (keyNum == 2)
    {
      in >> delCh{'\''} >> temp.key2 >> delCh{'\''};
    }
    if (keyNum == 3)
    {
      in >> delCh{'"'};
      std::getline(in, temp.key3, '"');
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
