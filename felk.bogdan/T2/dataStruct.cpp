#include "dataStruct.hpp"
#include <iomanip>
#include <sstream>

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
  using del = Delimeter;
  StreamGuard guard(in);
  in >> del{'('} >> del{':'};
  long long key1 = 0;
  size_t key2 = 0;
  std::string key3 = "";
  for (int i = 0; i < 3; i++)
  {
    std::string keyNum = "";
    in >> keyNum;
    if (keyNum == "key1")
    {
      in >> key1;
      in >> del{'l', false} >> del{'l', false};
      in >> del{':'};
    }
    else if (keyNum == "key2")
    {
      in >> std::hex >> key2 >> std::dec;
      in >> del{':'};
    }
    else if (keyNum == "key3")
    {
      in >> del{'"'};
      std::getline(in, key3, '"');
      in >> del{':'};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{')'};
  if (in)
  {
    data = DataStruct{key1, key2, key3};
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
