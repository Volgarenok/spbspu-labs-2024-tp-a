#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "input.hpp"

namespace ishmuratov
{
//  void print_element(const std::pair< std::string, value_t > pair, std::ostream & output);
  unit_t intersect_impl(const unit_t & first, const unit_t & second);
  unit_t union_impl(const unit_t & first, const unit_t & second);
  bool is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
  bool not_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
}

#endif
