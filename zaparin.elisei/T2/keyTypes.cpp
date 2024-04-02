#include "keyTypes.hpp"
#include "delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, KeyType&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimeter{ ":key" } >> exp.value;

  return in;
}

std::istream& zaparin::operator>>(std::istream& in, UllBin&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimeter{ "0b" } >> exp.value;

  return in;
}