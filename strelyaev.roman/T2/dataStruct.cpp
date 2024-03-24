#include "dataStruct.hpp"
#include <iomanip>
#include "streamGuard.hpp"

std::istream& strelyaev::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  DataStruct temp{0, 0, ""};
  using del = delimiter;
  int keys_cout = 3;
  in >> del{'('};
  int i = 0;
  while ((in) && (i != keys_cout))
  {
    in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
    int key_num = 0;
    in >> key_num;
    if (key_num == 1)
    {
      in >> temp.key1_ >> del{'u'} >> del{'l'} >> del{'l'};
      i++;
    }
    else if (key_num == 2)
    {
      in >> std::hex;
      in >> del{'0'} >> del{'x'} >> temp.key2_;
      i++;
    }
    else if (key_num == 3)
    {
      std::string a = "";
      in >> del{'"'};
      std::getline(in, temp.key3_, '"');
      i++;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{':'} >> del{')'};
  data = temp;
  return in;
}

std::ostream& strelyaev::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  out << "(:key1 " << data.key1_ << "ull:key2 0x" << std::hex << std::uppercase << data.key2_ << ":key3 \"" << data.key3_ << "\":)";
  return out;
}

bool strelyaev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1_ != other.key1_)
  {
    return key1_ < other.key1_;
  }
  if (key2_ != other.key2_)
  {
    return key2_ < other.key2_;
  }
  return key3_.size() < other.key3_.size();
}
