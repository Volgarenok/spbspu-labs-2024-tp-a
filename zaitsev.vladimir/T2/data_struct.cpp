#include "data_struct.hpp"
#include <string>
#include <cstring>
#include "delimiter.hpp"
#include "stream_guard.hpp"


bool zaitsev::DataStruct::operator<(const DataStruct& other) const
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

std::istream& zaitsev::operator>>(std::istream& in, DataStruct& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using delim = CharDelimiter;
  StreamGuard guard(in);
  in >> delim{ '(' } >> delim{ ':' };

  int read_vals = 0;
  for (size_t i = 0; i < 3; ++i)
  {
    char key[4]{};
    in >> key[0] >> key[1] >> key[2];
    if (std::strcmp(key, "key"))
    {
      in.setstate(std::ios::failbit);
    }
    int nmb = 0;
    in >> nmb;
    switch (nmb)
    {
    case 1:
    {
      in >> val.key1_ >> key[0] >> key[1] >> key[2] >> delim{ ':' };
      read_vals |= 0b1;
      if (std::strcmp(key, "ULL") && std::strcmp(key, "ull"))
      {
        in.setstate(std::ios::failbit);
      }
      break;
    }
    case 2:
    {
      in >> std::hex >> val.key2_ >> delim{ ':' };
      read_vals |= 0b10;
      break;
    }
    case 3:
    {
      std::getline(in, val.key3_, ':');
      if (val.key3_.size() < 3 || val.key3_[1] != '\"' || val.key3_[val.key3_.size() - 1] != '\"')
      {
        in.setstate(std::ios::failbit);
      }
      else
      {
        val.key3_ = val.key3_.substr(2, val.key3_.size() - 3);
        read_vals |= 0b100;
      }
      break;
    }
    default:
    {
      in.setstate(std::ios::failbit);
    }
    }
  }
  in >> delim{ ')' };
  if (read_vals ^ 0b111)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& zaitsev::operator<<(std::ostream& out, const DataStruct& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);

  out << "(:key1 " << val.key1_ << "ULL";
  out << ":key2 0x" << std::hex << std::uppercase << val.key2_;
  out << ":key3 \"" << std::nouppercase << val.key3_ << "\":)";

  return out;
}
