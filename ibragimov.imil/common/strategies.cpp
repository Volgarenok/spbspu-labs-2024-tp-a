#include "strategies.hpp"

#include <cctype>

bool ibragimov::formatters::CaseSensitive::isSame(const char l, const char r)
{
  return (l == r);
}
bool ibragimov::formatters::CaseInsensitive::isSame(const char l, const char r)
{
  return (std::tolower(l) == std::tolower(r));
}
