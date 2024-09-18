#include "format.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <functional>
#include "delimiter.hpp"

std::istream & erohin::operator>>(std::istream & input, DoubleFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  long long integer = 0;
  double fractional = 0.0;
  input >> integer >> fractional >> IgnoredCaseDelimiter{ 'd' };
  if (input)
  {
    dest.ref = integer + fractional * (integer >= 0 ? 1 : -1);
  }
  return input;
}

std::istream & erohin::operator>>(std::istream & input, LongLongFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> dest.ref >> IgnoredCaseDelimiter{ 'l' } >> IgnoredCaseDelimiter{ 'l' };
}

std::istream & erohin::operator>>(std::istream & input, StringFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return std::getline(input >> SensetiveCaseDelimiter{ dest.wrapper }, dest.ref, dest.wrapper);
}

std::istream & erohin::operator>>(std::istream & input, WordInContextFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string & str = dest.word;
  size_t wrap_size = dest.max_wrapper_size;
  input >> str;
  int (*isLetter)(int) = std::isalpha;
  auto front_found_iter = std::find_if(str.cbegin(), str.cend(), isLetter);
  size_t diff = std::distance(str.cbegin(), front_found_iter);
  if (front_found_iter != str.cbegin() && diff <= wrap_size)
  {
    str = str.substr(diff);
  }
  else if (diff > wrap_size)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  auto back_found_iter = std::find_if(str.crbegin(), str.crend(), isLetter);
  diff = std::distance(str.crbegin(), back_found_iter);
  if (back_found_iter != str.crbegin() && diff <= wrap_size)
  {
    str = str.substr(0, str.size() - diff);
  }
  else if (diff > wrap_size)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  int (*convertToLower)(int) = std::tolower;
  std::transform(str.begin(), str.end(), str.begin(), convertToLower);
  return input;
}
