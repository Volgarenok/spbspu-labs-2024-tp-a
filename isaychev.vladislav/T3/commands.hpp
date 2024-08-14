#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "polygon.hpp"

namespace isaychev
{
  using collection_t = std::vector< Polygon >;

  void do_area(std::istream & in, std::ostream & out, const collection_t & col);
  void do_max(std::istream & in, std::ostream & out, const collection_t & col);
  void do_min(std::istream & in, std::ostream & out, const collection_t & col);
  void do_count(std::istream & in, std::ostream & out, const collection_t & col);
  void do_maxseq(std::istream & in, std::ostream & out, const collection_t & col);
  void do_intersections(std::istream & in, std::ostream & out, const collection_t & col);
}

#endif
