#include "keyTypes.hpp"
#include <string>
#include <delimeter.hpp>

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

std::istream& zaparin::operator>>(std::istream& in, RatLsp&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimeter{ "(:N" } >> exp.value.first >> Delimeter{ ":D" } >> exp.value.second >> Delimeter{ ":)" };

  return in;
}

std::istream& zaparin::operator>>(std::istream& in, String&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimeter{ "\"" };
  std::getline(in, exp.value, '\"');

  return in;
}


