#include "path_search.hpp"
#include <vector>
#include <limits>

constexpr int inf = std::numeric_limits< int >::max();

std::vector<std::vector<int>> create_adjacency_matrix(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  std::vector<std::vector<int>> matrix(graph.size(), std::vector<int>(graph.size(), inf));

  size_t i = 0, j = 0;
  for (graph_t::const_iterator it_i = graph.begin(); it_i != graph.end(); ++it_i)
  {
    j = 0;
    for (unit_t::const_iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
    {
      matrix[i][j] = it_j->second;
    }
    ++i;
  }
  return matrix;
}