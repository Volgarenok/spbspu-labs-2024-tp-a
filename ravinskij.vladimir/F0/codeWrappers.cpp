#include "codeWrappers.hpp"
#include <iostream>
#include <iterator>
#include <scopeGuard.hpp>
#include <delimeters.hpp>

namespace rav = ravinskij;
std::ostream& rav::operator<<(std::ostream& out, rav::WriteWrapper&& wrapper)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '"' <<  wrapper.symbol << '"' << '-';
  using output_it_t = std::ostream_iterator< bool >;
  std::copy(wrapper.code.cbegin(), wrapper.code.cend(), output_it_t{ out, "" });
  out << '-' << wrapper.frequency;
  return out;
}

std::istream& rav::operator>>(std::istream& in, rav::ReadWrapper&& wrapper)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = CharDelimeter;
  in >> std::noskipws;
  in >> del{ '"' } >> wrapper.symbol >> del{ '"' } >> del{ '-' };
  if (!in)
  {
    return in;
  }
  char bit = 0;
  while (in && bit != '-')
  {
    in >> bit;
    wrapper.code.push_back(static_cast< bool >(bit - '0'));
  }
  wrapper.code.pop_back();
  in >> wrapper.frequency;
  in >> std::skipws;
  return in;
}
