#include "dataStruct.hpp"

#include <iomanip>
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& allaberdiev::operator>>(std::istream& in, DataStruct& ds)
{
  DataStruct temp{0, {0, 0}, ""};
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  in >> std::noskipws;
  int keys = 3;
  in >> Delimiter{'('};
  while ((in) && (keys != 0))
  {
    in >> Line{":key"};
    int k_num = 0;
    in >> k_num;
    if (k_num == 1)
    {
      double r = 0, i = 0;
      in >> Line{" #c("} >> r >> Delimiter{' '} >> i >> Delimiter{')'};
      temp.key1.real(r);
      temp.key1.imag(i);
    }
    else if (k_num == 2)
    {
      in >> Line{" (:N "} >> temp.key2.first >> Line{":D "}
          >> temp.key2.second >> Line{":)"};
    }
    else if (k_num == 3)
    {
      in >> Line{" \""};
      std::getline(in, temp.key3, '"');
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> Line{":)"};
  ds = temp;
  return in;
}

std::ostream& allaberdiev::operator<<(std::ostream& out, const DataStruct& ds)
{
  out << std::fixed << std::setprecision(1);
  out << "(:key1 #c(" << ds.key1.real() << " " << ds.key1.imag() << "):"
      << "key2 (:N " << ds.key2.first << ":D " << ds.key2.second << "):"
      << "key3 \"" << ds.key3 << "\":)";
  return out;
}

bool allaberdiev::operator<(const DataStruct& l, const DataStruct& r)
{
  double mod_l = std::abs(l.key1);
  double mod_r = std::abs(r.key1);

  if (mod_l != mod_r)
  {
    return mod_l < mod_r;
  }
  if (l.key2 != r.key2)
  {
    return l.key2 < r.key2;
  }
  return l.key3.length() < r.key3.length();
}
