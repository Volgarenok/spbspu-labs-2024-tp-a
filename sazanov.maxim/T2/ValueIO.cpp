#include "ValueIO.hpp"
#include <iostream>
#include <bitset>
#include "DelimiterI.hpp"

std::istream& sazanov::operator>>(std::istream& in, BinUllI&& value)
{
  in >> StrictCaseDelimiterI{'0'} >> AnyCaseDelimiterI{'b'};
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string binKey;
  std::getline(in, binKey, ':');
  try
  {
    value.number = std::stoull(binKey, nullptr, 2);
  }
  catch (const std::logic_error& e)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const BinUllO&& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '0';
  std::string binNum = std::bitset< sizeof(unsigned long long) * 8 >(value.number).to_string();
  binNum.erase(0, binNum.find_first_not_of('0'));
  out << binNum;
  return out;
}

std::istream& sazanov::operator>>(std::istream& in, CharKeyI&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> StrictCaseDelimiterI{'\''} >> value.ch >> StrictCaseStringDelimiterI{"':"};
  return in;
}

std::istream& sazanov::operator>>(std::istream& in, StringKeyI&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::cin >> StrictCaseDelimiterI{'"'};
  std::getline(in, value.str, '"');
  std::cin >> StrictCaseDelimiterI{':'};
  return in;
}
