#include "dataStruct.hpp"
#include <iostream>
#include <iomanip>
#include <complex>
#include "delimeter.hpp"

std::istream & isaychev::operator>>(std::istream & in, DataStruct & obj)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }

  in >> std::noskipws;
  using dc = delim_ch_t;
  using ds = delim_str_t;

  in >> ds{"(:"};

  long long num = 0ll;
  double real = 0.0, imag = 0.0;
  std::string str = "";
  for (int i = 0; i < 3; ++i)
  {
    in >> str;
    if (str == "key1")
    {
      in >> dc{' '};
      std::getline(in, str,':');
      try
      {
        num = std::stoll(str);
      }
      catch (const std::invalid_argument &)
      {
        in.setstate(std::ios::failbit);
      }
    }
    else if (str == "key2")
    {
      in >> ds{" #c("};
      std::getline(in, str,')');
      size_t b = 0;
      try
      {
        real = std::stod(str, &b);
        imag = std::stod(str.substr(b));
      }
      catch (const std::invalid_argument &)
      {
        in.setstate(std::ios::failbit);
      }
      in >> dc{':'};
    }
    else if (str == "key3")
    {
      in >> ds{" \""};
      std::getline(in, str, '"');
      in >> dc{':'};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }

  }

  in >> dc{')'};

  if (in)
  {
    obj.key1 = num;
    obj.key2 = std::complex< double >(real, imag);
    obj.key3 = str;
  }

  in >> std::skipws;
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const DataStruct & obj)
{
  out << std::fixed << std::setprecision(1);
  out << "(:key1 " << obj.key1 << "ll";
  out << ":key2 #c(" << obj.key2.real() << " " << obj.key2.imag() << ")";
  out << ":key3 \"" << obj.key3 << "\":)";
  return out;
}
