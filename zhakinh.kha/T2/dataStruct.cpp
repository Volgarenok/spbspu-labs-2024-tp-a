#include "dataStruct.hpp"
#include <iostream>
#include <iomanip>
#include "delimiter.hpp"
#include "streamGuard.hpp"

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
    in >> del{ ':' } >> del{ 'k' } >> del{ 'e' } >> del{ 'y' };
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
      long long value = 0;
      in >> value;
      data.key2 = value;
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
  out << std::fixed;
  out << "(:key1 " << std::setprecision(1) << data.key1 << "d:key2 ";
  out << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
  return out;
}

std::ostream& operator<<(std::ostream & out, const std::pair<long long, unsigned long long>&pair)
{
  out << '(' << pair.first << ':' << pair.second << ')';
  return out;
}

std::istream& operator>>(std::istream & in, std::pair<long long, unsigned long long>&pair)
{
  char ch;
  if (in >> ch && ch == '(' && in >> pair.first >> ch && ch == ':' && in >> pair.second >> ch && ch == ')')
  {
    return in;
  }
  in.setstate(std::ios::failbit);
  return in;
}
