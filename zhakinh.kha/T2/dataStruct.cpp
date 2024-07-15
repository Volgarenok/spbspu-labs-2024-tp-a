#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

std::istream& operator>>(std::istream& in, const zhakha::Delimiter& d)
{
  char c;
  if (!(in >> c) || c != d.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, double& key1)
{
  in >> key1;
  return in;
}

std::istream& operator>>(std::istream& in,
std::pair<long long, unsigned long long>& key2)
{
  in >> key2.first >> key2.second;
  return in;
}

std::istream& operator>>(std::istream& in, std::string& key3)
{
  std::getline(in, key3, '\"');
  return in;
}

std::istream& zhakha::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  using del = zhakha::Delimiter;
  in >> del{ '(' };
  for (int i = 0; i < 3; i++)
  {
    in >> del{ ':' };
    in >> del{ 'k' } >> del{ 'e' } >> del{ 'y' };
    int key_num = 0;
    in >> key_num;
    if (key_num == 1)
    {
      double value = 0;
      in >> value;
      data.key1 = value;
      in >> del{ 'd' };
    }
    else if (key_num == 2)
    {
      long long num = 0;
      unsigned long long denom = 0;
      in >> num >> denom;
      data.key2 = { num, denom };
      in >> del{ 'l' } >> del{ 'l' };
    }
    else if (key_num == 3)
    {
      std::string value = "";
      in >> del{ '"' };
      std::getline(in, value, '\"');
      data.key3 = value;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{ ':' } >> del{ ')' };
  return in;
}

std::ostream& zhakha::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  out << "(:key1 0x" << std::hex << std::uppercase << data.key1 << std::nouppercase << std::dec;
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}

bool zhakha::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}
