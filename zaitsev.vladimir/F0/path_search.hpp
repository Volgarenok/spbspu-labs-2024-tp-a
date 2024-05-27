#ifndef PATH_SEARCH_HPP
#define PATH_SEARCH_HPP
#include "graphs_base.hpp"

namespace zaitsev
{
  void shortest_path(std::istream& in, std::ostream& out, const base_t& graphs);
  void shortest_paths_matrix(std::istream& in, std::ostream& out, const base_t& graphs);
  void shortest_path_trace(std::istream& in, std::ostream& out, const base_t& graphs);
  void check_negative_weight_cycles(std::istream& in, std::ostream& out, const base_t& graphs);
}
#endif
