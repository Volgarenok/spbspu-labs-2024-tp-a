#include "path_search.hpp"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <limits>

constexpr int inf = std::numeric_limits< int >::max();

struct edge
{
  size_t i;
  size_t j;
  int cost;
};

std::vector<std::vector<int>> create_adjacency_matrix(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  std::vector<std::vector<int>> matrix(graph.size(), std::vector<int>(graph.size(), inf));

  std::unordered_map< std::string, size_t > vert_indexes(graph.size());
  size_t index = 0;
  for (graph_t::const_iterator i = graph.begin(); i != graph.end(); ++i, ++index)
  {
    vert_indexes[i->first] = index;
  }

  size_t i = 0;
  for (graph_t::const_iterator it_i = graph.begin(); it_i != graph.end(); ++it_i)
  {
    for (unit_t::const_iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
    {
      matrix[i][vert_indexes[it_j->first]] = it_j->second;
    }
    ++i;
  }
  return matrix;
}

std::vector< edge > extract_edges(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;

  std::unordered_map< std::string, size_t > vert_indexes(graph.size());
  size_t edges_nmb = 0;
  size_t index = 0;
  for (graph_t::const_iterator i = graph.begin(); i != graph.end(); ++i, ++index)
  {
    edges_nmb += i->second.size();
    vert_indexes[i->first] = index;
  }
  std::vector< edge > edges_list(edges_nmb);
  size_t i = 0, k = 0;
  for (graph_t::const_iterator it_i = graph.begin(); it_i != graph.end(); ++it_i)
  {
    for (unit_t::const_iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
    {
      edges_list[k] = { i, vert_indexes[it_j->first], it_j->second };
    }
    ++i;
  }
  return edges_list;
}

std::vector< std::vector< int > > calc_paths_floyd(const std::vector<std::vector<int>>& matrix)
{
  std::vector<std::vector<int>> dist(matrix.size(), std::vector<int>(matrix.size(), inf));
  for (int k = 0; k < matrix.size(); ++k)
  {
    for (int i = 0; i < matrix.size(); ++i)
    {
      for (int j = 0; j < matrix.size(); ++j)
      {
        if (dist[i][k] < inf && dist[k][j] < inf)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

std::vector< int > calc_paths_ford(const std::vector< std::vector< int > >& matrix, size_t begin)
{
  std::vector<int> d(matrix.size(), inf);
  d[begin] = 0;
  std::vector<int> p(matrix.size(), -1);
  for (;;)
  {
    bool any = false;
    for (int j = 0; j < m; ++j)
      if (d[e[j].a] < inf)
        if (d[e[j].b] > d[e[j].a] + e[j].cost)
        {
          d[e[j].b] = d[e[j].a] + e[j].cost;
          p[e[j].b] = e[j].a;
          any = true;
        }
    if (!any)  break;
  }

  if (d[t] == inf)
    cout << "No path from " << v << " to " << t << ".";
  else {
    std::vector<int> path;
    for (int cur = t; cur != -1; cur = p[cur])
      path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << "Path from " << v << " to " << t << ": ";
    for (size_t i = 0; i < path.size(); ++i)
      cout << path[i] << ' ';
  }
}