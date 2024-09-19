#include "dataStruct.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool felk::DataStruct::operator<(const felk::DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.size() < other.key3.size();
}

std::istream& felk::operator>>(std::istream& in, felk::DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct temp;
  using del = Delimeter;
  StreamGuard guard(in);
  in >> del{'('} >> del{':'};
  std::string keyNum = "";
  for (int i = 0; i < 3; i++)
  {
    in >> keyNum;
    if (keyNum == "key1")
    {
      in >> WrapperLL{temp.key1};
    }
    else if (keyNum == "key2")
    {
      in >> WrapperHex{temp.key2};
    }
    else if (keyNum == "key3")
    {
      in >> WrapperStr{temp.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> del{':'};
  }
  in >> del{')'};
  if (in)
  {
    data = temp;
  }
  return in;
}
std::ostream& felk::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
     return out;
  }
  StreamGuard StreamGuard(out);
  out << "(:key1 ";
  out << data.key1 << "ll";
  out << ":key2 0x" << std::uppercase << std::hex;
  out << data.key2 << std::dec;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
