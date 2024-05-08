#include "dataStruct.hpp"
#include <iomanip>
#include "streamGuard.hpp"
#include "delimiter.hpp"


std::istream& altun::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  using del = Delimiter;
  int dnumber = 0;
  in >> del{'('};
  int max_keys = 3;
  for (int i = 0; i < max_keys; i++)
  {
    in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
    in >> dnumber;
    if (dnumber == 1)
    {
      in >> data.key1 >> del{'d'};
    }
    else if (dnumber == 2)
    {
      in >> data.key2;
    }
    else if (dnumber == 3)
    {
      in >> del{'"'};
      std::getline(in, data.key3, '"');
    }
  }
  in >> del{':'} >> del{')'};
  return in;
}
std::ostream& altun::operator<<(std::ostream& out, const DoubleScience& data)
{
  double dnum = data.data_;
  StreamGuard s_guard(out);
  out << std::fixed << std::setprecision(1);
  int exp = 0;
  char sign = 0;
  if (dnum == 0)
  {
    out << dnum;
    return out;
  }
  if (dnum >= 1.0)
  {
    while (dnum > 1.0)
    {
      dnum /= 10;
      exp++;
    }
    sign = '+';
  }
  else
  {
    while (dnum < 1.0)
    {
      dnum *= 10;
      exp++;
    }
    sign = '-';
  }
  out << dnum << 'e' << sign << exp;
  return out;
}
std::ostream& altun::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  out << "(:key1 " <<  std::setprecision(1) << std::fixed << data.key1;
  out << "d:key2 ";
  out << DoubleScience{data.key2};
  out << ":key3 " << '"' << data.key3 << "\":)";
  return out;
}
bool altun::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}
