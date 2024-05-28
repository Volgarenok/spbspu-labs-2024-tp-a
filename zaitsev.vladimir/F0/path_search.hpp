#ifndef PATH_SEARCH_HPP
#define PATH_SEARCH_HPP
#include "graphs_base.hpp"

namespace zaitsev
{
  void shortest_distance(const base_t& graphs, std::istream& in, std::ostream& out);
  void shortest_path_trace(const base_t& graphs, std::istream& in, std::ostream& out);
  void shortest_paths_matrix(const base_t& graphs, std::istream& in, std::ostream& out);
  void check_negative_weight_cycles(const base_t& graphs, std::istream& in, std::ostream& out);
}
#endif
