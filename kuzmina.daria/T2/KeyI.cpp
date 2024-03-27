#include "KeyI.hpp"
#include <istream>
#include <string>
#include "DelimiterI.hpp"

std::istream& kuzmina::operator>>(std::istream& in, SLLKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  long long temp = 0;
  in >> temp >> DelimiterIStr{ "ll" };

  if (in)
  {
    key.value = temp;
  }

  return in;
}

std::istream& kuzmina::operator>>(std::istream& in, RATKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  long long tempN = 0;
  unsigned long long tempD = 0;
  in >> DelimiterIStr{ "(:N" } >> tempN >> DelimiterIStr{ ":D" } >> tempD >> DelimiterIStr{ ":)" };

  if (in)
  {
    key.value = { tempN, tempD };
  }

  return in;
}

std::istream& kuzmina::operator>>(std::istream& in, STRKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::string tempStr = "";
  std::getline(in >> DelimiterI{ '"' }, tempStr, '"');

  if (in)
  {
    key.value = tempStr;
  }

  return in;
}
