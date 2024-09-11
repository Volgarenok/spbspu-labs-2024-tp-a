#include "dataStruct.hpp"

#include <complex>
#include <iomanip>

#include <delimiter.hpp>
#include <streamGuard.hpp>

std::istream &zagrivnyy::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = zagrivnyy::DelimiterI;
  in >> del{"("};

  // clang-format off
  zagrivnyy::DataStruct tmp{0, {0., 0.}, ""};
  // clang-format on

  const size_t KEYS_TO_READ = 3;
  for (size_t i = 0; (i < KEYS_TO_READ) && in; ++i)
  {
    size_t keyIndex = 0;
    in >> del{":key"} >> keyIndex;
    switch (keyIndex)
    {
    case 1:
      zagrivnyy::parseInput(in, tmp.key1);
      break;
    case 2:
      zagrivnyy::parseInput(in, tmp.key2);
      break;
    case 3:
      zagrivnyy::parseInput(in, tmp.key3);
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> del{":)"};
  if (in)
  {
    data = tmp;
  }

  return in;
}

std::ostream &zagrivnyy::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  zagrivnyy::StreamGuard streamGuard(out);

  out << "(:key1 '" << std::setprecision(1) << std::fixed << data.key1 << "':key2 #c(" << data.key2.real() << " ";
  out << data.key2.imag() << "):key3 \"" << data.key3 << "\":)";

  return out;
}

void zagrivnyy::parseInput(std::istream &in, char &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  using del = zagrivnyy::DelimiterI;
  char tmp = 0;
  in >> del{"'"} >> tmp >> del{"'"};

  if (in)
  {
    data = tmp;
  }
}

void zagrivnyy::parseInput(std::istream &in, std::complex< double > &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  using del = zagrivnyy::DelimiterI;
  double real = 0.;
  double imag = 0.;
  in >> del{"#c("} >> real >> imag >> del{")"};

  std::complex< double > tmp{real, imag};
  if (in)
  {
    data = tmp;
  }
}

void zagrivnyy::parseInput(std::istream &in, std::string &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  using del = zagrivnyy::DelimiterI;
  in >> del{"\""};
  std::getline(in, data, '"');
}

bool zagrivnyy::DataStruct::operator<(const DataStruct &src) const
{
  if (key1 == src.key1)
  {
    if (key2 == src.key2)
    {
      return key3.length() < src.key3.length();
    }
    return std::abs(key2) < std::abs(src.key2);
  }
  return key1 < src.key1;
}
