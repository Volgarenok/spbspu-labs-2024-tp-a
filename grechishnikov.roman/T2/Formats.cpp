#include "Formats.hpp"
#include <delimiter.hpp>
#include <scopeGuard.hpp>

std::istream& grechishnikov::operator>>(std::istream& in, OctFormat&& key1)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{ '0' };
  ScopeGuard sGuard(in);
  size_t key = 0;
  in >> std::oct >> key;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  key1.key = key;
  return in;
}

std::istream& grechishnikov::operator>>(std::istream& in, ComplexFormat&& key2)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{ '#' } >> Delimiter{ 'c' } >> Delimiter{ '(' };
  double keyR = 0;
  double keyI = 0;
  in >> keyR >> keyI;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  std::complex< double > res(keyR, keyI);
  key2.key = res;
  in >> Delimiter{ ')' };
  return in;
}

std::istream& grechishnikov::operator>>(std::istream& in, StringFormat&& key3)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{ '\"' };
  std::string key = "";
  std::getline(in, key, '\"');
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  key3.key = key;
  return in;
}


