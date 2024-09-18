#include "utilities.hpp"
#include <algorithm>
#include <functional>

bool ishmuratov::is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second)
{
  return second.find(pair.first) != second.cend();
}

bool ishmuratov::not_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second)
{
  return second.find(pair.first) == second.cend();
}

ishmuratov::unit_t ishmuratov::intersect_impl(const unit_t & first, const unit_t & second)
{
  unit_t inter_dict;
  auto pred = std::bind(is_inside, std::placeholders::_1, std::cref(second));
  std::copy_if(first.cbegin(), first.cend(), std::inserter(inter_dict, inter_dict.end()), pred);
  return inter_dict;
}

ishmuratov::unit_t ishmuratov::union_impl(const unit_t & first, const unit_t & second)
{
  unit_t union_dict;
  std::copy(first.cbegin(), first.cend(), std::inserter(union_dict, union_dict.end()));
  auto pred = std::bind(not_inside, std::placeholders::_1, std::cref(first));
  std::copy_if(second.cbegin(), second.cend(), std::inserter(union_dict, union_dict.end()), pred);
  return union_dict;
}