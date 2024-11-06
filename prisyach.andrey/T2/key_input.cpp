#include "key_input.hpp"
#include <cmath>
#include "streamguard.hpp"
#include "delimiters.hpp"

std::istream & prisyach::operator>>(std::istream & in, FirstKey && key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    int numBefore = 0;
    int numAfter = 0;
    int power = 0;
    in >> numBefore >> DelimiterChar{ '.' } >> numAfter >> DelimiterChar{ 'e' } >> power;
    if (in)
    {
      key.data = (numBefore + numAfter * 0.01) * std::pow(10, power);
    }
    return in;
  }
}

std::istream & prisyach::operator>>(std::istream & in, SecondKey && key)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    unsigned long long octNum = 0;
    in >> DelimiterChar{'0'} >> std::oct >> octNum;
    if (in)
    {
      key.data = octNum;
    }
    return in;
  }
}

std::istream & prisyach::operator>>(std::istream & in, ThirdKey && key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    std::string str = "";
    in >> DelimiterChar{'\"'};
    std::getline(in, str, '\"');
    if (in)
    {
      key.data = str;
    }
    return in;
  }
}