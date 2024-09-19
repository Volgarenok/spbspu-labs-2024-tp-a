#include "CrossRefs.hpp"

#include <unordered_map>
#include <iterator>
#include <string>
#include <algorithm>

std::unordered_map<std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::begin()
{
  return table_.begin();
}
std::unordered_map<std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::end()
{
  return table_.end();
}
std::unordered_map<std::string, std::list< size_t > >::const_iterator stepanchenko::CrossRefs::search(const std::string& word) const
{
  return table_.find(word);
}
