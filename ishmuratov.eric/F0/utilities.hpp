#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "input.hpp"

namespace ishmuratov
{
  unit_t intersect_impl(const unit_t & first, const unit_t & second);
  unit_t union_impl(const unit_t & first, const unit_t & second);
  bool is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
  bool not_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
}

#endif
