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
  using del = Delimiter;
  DataStruct temp{0, 0, ""};
  int keyCount = 3;
  in >> del{"("};
  for (int i = 0; i < keyCount; i++)
  {
    int keyNum = 0;
    in >> del{":key"} >> keyNum;
    if (keyNum = 1)
    {
      in >> std::hex;
      in >> del{"0x"} >> temp.key1;
    }
    if (keyNum = 2)
    {
      in >> del{"\""} >> temp.key2 >> del{"\""};
    }
    if (keyNum = 3)
    {
      in >> del{"\""};
      std::getline(in, temp.key3, '\"');
    }
  }
  in >> del{":)"};
  data = temp;
  return in;
}
