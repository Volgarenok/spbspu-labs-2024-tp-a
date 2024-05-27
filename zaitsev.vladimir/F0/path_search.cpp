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


std::vector< std::vector< int > > calc_paths_floyd(const std::vector<std::vector<int>>& matrix)
{
  std::vector<std::vector<int>> paths(matrix.size(), std::vector<int>(matrix.size(), inf));
  for (int k = 0; k < matrix.size(); ++k)
  {
    for (int i = 0; i < matrix.size(); ++i)
    {
      for (int j = 0; j < matrix.size(); ++j)
      {
        if (paths[i][k] < inf && paths[k][j] < inf)
        {
          paths[i][j] = std::min(paths[i][j], paths[i][k] + paths[k][j]);
        }
      }
    }
  }
  return paths;
}
