#include "delimiter.hpp"
#include <cctype>
#include <iomanip>
#include <ios>
#include <string>

std::istream& ibragimov::operator>>(std::istream& in, const CharDelimiterI&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = ' ';
    in >> c;
    if (in && (c != expectation.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, const AnyCaseCharDelimiterI&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = ' ';
    in >> c;
    if (in && (std::tolower(c) != std::tolower(expectation.expected)))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, const StringDelimiterI&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    std::string str = " ";
    size_t strLength = expectation.expected.length();
    in >> std::setw(strLength) >> str;
    if (in && (str != expectation.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
