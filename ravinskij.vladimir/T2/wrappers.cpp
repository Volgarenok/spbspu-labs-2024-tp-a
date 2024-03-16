#include <bitset>
#include <string>
#include "wrappers.hpp"
#include "delimeters.hpp"
#include "scopeGuard.hpp"

std::istream& ravinskij::operator>>(std::istream& in, BinUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }
  using del = CharDelimeter;
  ScopeGuard scopeGuard(in);
  in >> del{'0'} >> del{'B'};

  std::string binary;
  std::getline(in ,binary, ':');

  constexpr size_t BIN_ULL_SIZE = 64;
  std::bitset< BIN_ULL_SIZE > bs(binary);
  data.value = bs.to_ullong();
  return in;
}

std::istream& ravinskij::operator>>(std::istream& in, HexUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using del = CharDelimeter;
  ScopeGuard scopeGuard(in);
  in >> del{'0'} >> del{'X'};
  in >> std::hex;
  in >> data.value;
  return in;
}
