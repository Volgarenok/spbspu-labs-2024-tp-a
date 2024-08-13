#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace isaychev
{
  using collection_t = std::vector< Polygon >;
  bool is_even(const Polygon & rhs);
  bool is_odd(const Polygon & rhs);
  bool is_right_amount(const Polygon & rhs, size_t amount);

  void do_area(std::istream & in, std::ostream & out, const collection_t & col);
  void do_max(std::istream & in, std::ostream & out, const collection_t & col);
  void do_min(std::istream & in, std::ostream & out, const collection_t & col);
  void do_count(std::istream & in, std::ostream & out, const collection_t & col);
  void do_maxseq(std::istream & in, std::ostream & out, const collection_t & col);
//  void doIntersectionsCmd(std::istream & in, std::ostream & out, const collection_t & col);
}

#endif
