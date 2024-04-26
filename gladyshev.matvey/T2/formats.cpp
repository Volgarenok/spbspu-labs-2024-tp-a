#include "formats.hpp"

#include <algorithm>
#include <cmath>

#include "delimiter.hpp"

std::istream& gladyshev::operator>>(std::istream& in, CharKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{"'"} >> value.key >> Delimiter{"':"};
  return in;
}

std::istream& gladyshev::operator>>(std::istream& in, SciKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string supstr = "";
  std::getline(in, supstr, ':');
  std::transform(supstr.cbegin(), supstr.cend(), supstr.begin(), ::tolower);
  double mantissa = 0;
  int num = 0;
  if (supstr.find('e') != std::string::npos)
  {
    mantissa = std::stod(supstr.substr(0, supstr.find('e')));
    num = std::stoi(supstr.substr(supstr.find('e') + 1));
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  if (mantissa < 1 || mantissa >= 10)
  {
    in.setstate(std::ios::failbit);
  }
  value.key = mantissa * std::pow(10, num);
  return in;
}

std::istream& gladyshev::operator>>(std::istream& in, StrKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{"\""};
  std::getline(in, value.key, '"');
  in >> Delimiter{":"};
  return in;
}
