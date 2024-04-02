#include "outputData.hpp"

#include <iomanip>
#include <iostream>

#include "dataStruct.hpp"

namespace zhalilov
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios < char > &s):
      s_(s),
      fill_(s.fill()),
      precision_(s.precision()),
      fmt_(s.flags())
    {}

    ~iofmtguard()
    {
      s_.fill(fill_);
      s_.precision(precision_);
      s_.flags(fmt_);
    }

  private:
    std::basic_ios < char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios < char >::fmtflags fmt_;
  };
}

std::ostream &zhalilov::operator<<(std::ostream &out, const DataStruct &data)
{
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1) << std::scientific;
  out << "(:key1 " << data.key1;
  out << ":key2 " << data.key2 << "ll";
  out << ":key3 ";
  out << std::quoted(data.key3);
  out << ":)";
  return out;
}
