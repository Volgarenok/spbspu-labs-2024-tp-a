#include "DelimiterI.hpp"
#include <istream>
#include <cctype>
#include <string>

std::istream& kuzmina::operator>>(std::istream& in, DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;

  if (in && std::tolower(c) != std::tolower(exp.expected))
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& kuzmina::operator>>(std::istream& in, DelimiterIStr&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  for (size_t i = 0; exp.expected[i] != '\0'; ++i)
  {
    in >> DelimiterI{ exp.expected[i] };
  }

  return in;
}

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
    key.value.first = tempN;
    key.value.second = tempD;
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
