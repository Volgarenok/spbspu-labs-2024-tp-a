#include "label.hpp"

bool ibragimov::CaseSensitive::isSame(const char lChar, const char rChar)
{
  return (lChar == rChar);
}
bool ibragimov::CaseInsensitive::isSame(const char lChar, const char rChar)
{
  return (std::tolower(lChar) == std::tolower(rChar));
}
