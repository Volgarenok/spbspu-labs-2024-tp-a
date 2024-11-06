#include "datastruct.hpp"
#include <complex>
#include <string>
#include <iomanip>
#include <scopeguard.hpp>
#include <iotypes.hpp>

bool agarkov::Comparator::operator()(const DataStruct& lhs, const DataStruct& rhs) const
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else
  {
    if (lhs.key2 != rhs.key2)
    {
      return std::abs(lhs.key2) < std::abs(rhs.key2);
    }
    return lhs.key3.length() < lhs.key3.length();
  }
}

std::istream& agarkov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  iofmtguard fmtguard(in);

  char key1 = '\0';
  std::complex< double > key2(0.0, 0.0);
  std::string key3 = "";

  bool isKey1 = false;
  bool isKey2 = false;
  bool isKey3 = false;

  in >> DelimiterIO{'('} >> DelimiterIO{':'};
  for (size_t i = 0; i < 3; ++i)
  {
    std::string key;
    in >> key;
    if (key == "key1" && !isKey1)
    {
      in >> CharIO{key1} >> DelimiterIO{':'};
    }
    else if (key == "key2" && !isKey2)
    {
      in >> ComplexIO{key2} >> DelimiterIO{':'};
    }
    else if (key == "key3" && !isKey3)
    {
      in >> StringIO{key3} >> DelimiterIO{':'};
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  in >> DelimiterIO{')'};
  if (in)
  {
    data = DataStruct{key1, key2, key3};
  }
  return in;
}

std::ostream& agarkov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 \'" << data.key1 << '\'';
  out << std::fixed << std::setprecision(1);
  out << ":key2 #c(" << data.key2.real() << " " << data.key2.imag();
  out << "):key3 \"" << data.key3 << "\":)";
  return out;
}
