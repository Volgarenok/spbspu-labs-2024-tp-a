#include "Delimiters.hpp"
#include <algorithm>
#include "StreamGuard.hpp"

std::istream& kozakova::operator>>(std::istream& in, kozakova::DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string s = "";
  std::getline(in, s, ':');
  std::string expUp = exp.expected;
  std::transform(exp.expected.begin(), exp.expected.end(), exp.expected.begin(), ::tolower);
  if ((strcmp(s.c_str(), exp.expected.c_str()) && strcmp(s.c_str(), expUp.c_str())))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
};

std::istream& kozakova::operator>>(std::istream& in, kozakova::DelimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  kozakova::StreamGuard sguard(in);
  char c = 0;
  in >> c;
  if (!(c == exp.expected || c == tolower(exp.expected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
};
