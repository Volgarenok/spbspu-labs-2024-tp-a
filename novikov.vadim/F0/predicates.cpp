#include "predicates.hpp"

bool novikov::contains(const std::string& lhs, const std::string& rhs)
{
  return lhs.find(rhs) != std::string::npos;
}
