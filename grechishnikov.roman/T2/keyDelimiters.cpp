#include "keyDelimiters.hpp"
#include "delimiter.hpp"
#include "scopeGuard.hpp"

grechishnikov::Key1_Delimiter::Key1_Delimiter(size_t& val):
  key(val)
{}

std::istream& grechishnikov::operator>>(std::istream& in, Key1_Delimiter&& key1)
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


grechishnikov::Key2_Delimiter::Key2_Delimiter(std::complex< double >& val):
  key(val)
{}

std::istream& grechishnikov::operator>>(std::istream& in, Key2_Delimiter&& key2)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{ '#' } >> Delimiter{ 'c' } >> Delimiter{ '(' };

  size_t keyR = 0;
  size_t keyI = 0;
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

grechishnikov::Key3_Delimiter::Key3_Delimiter(std::string& val):
  key(val)
{}

std::istream& grechishnikov::operator>>(std::istream& in, Key3_Delimiter&& key3)
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


