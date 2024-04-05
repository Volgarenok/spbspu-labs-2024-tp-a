#include "label.hpp"

bool ibragimov::formatters::CaseSensitive::isSame(const char lChar, const char rChar)
{
  return (lChar == rChar);
}
bool ibragimov::formatters::CaseInsensitive::isSame(const char lChar, const char rChar)
{
  return (std::tolower(lChar) == std::tolower(rChar));
}
