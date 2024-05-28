#ifndef PATH_SEARCH_HPP
#define PATH_SEARCH_HPP
#include "graphs_base.hpp"

namespace zaitsev
{
  void findShortestDistance(const base_t& graphs, std::istream& in, std::ostream& out);
  void findShortestPathTtrace(const base_t& graphs, std::istream& in, std::ostream& out);
  void printShortestPathsMatrix(const base_t& graphs, std::istream& in, std::ostream& out);
  void checkNegativeWeightCycles(const base_t& graphs, std::istream& in, std::ostream& out);
}
#endif
