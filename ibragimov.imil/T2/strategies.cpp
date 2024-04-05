#include "strategies.hpp"

#include <cctype>

bool ibragimov::strategies::CaseSensitive::isSame(const char lChar, const char rChar)
{
  return (lChar == rChar);
}
bool ibragimov::strategies::CaseInsensitive::isSame(const char lChar, const char rChar)
{
  return (std::tolower(lChar) == std::tolower(rChar));
}
