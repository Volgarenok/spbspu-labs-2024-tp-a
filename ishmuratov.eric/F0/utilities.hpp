#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <map>
#include <list>
#include <functional>

namespace ishmuratov
{
  using pair_t = std::pair< std::string, std::list< std::string> >;
  using value_t = std::list< std::string >;
  using unit_t = std::map< std::string, value_t >;
  using dict_t = std::map< std::string, unit_t >;
  using func_t = std::function< unit_t(const unit_t &, const unit_t &) >;

  void process_operations(dict_t & dictionaries, std::istream & input, func_t operation);
  unit_t intersect_impl(const unit_t & first, const unit_t & second);
  unit_t union_impl(const unit_t & first, const unit_t & second);
  bool is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
  bool not_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second);
  std::ostream & print_pair_transform(const pair_t & pair, std::ostream & output);
  std::ostream & operator<<(std::ostream & output, const unit_t & dict);
}

#endif
