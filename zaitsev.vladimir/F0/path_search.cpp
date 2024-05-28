#include "path_search.hpp"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <limits>
#include <stream_guard.hpp>

constexpr int inf = std::numeric_limits< int >::max();

struct edge
{
  size_t a;
  size_t b;
  int val;
};
using std::vector;
vector<vector<int>> create_adjacency_matrix(const zaitsev::graph_t& graph);
vector< edge > extract_edges(const zaitsev::graph_t& graph);
vector< vector< int > > calc_paths_floyd(const vector< vector< int > >& matrix);
std::pair<vector< int >, vector< size_t >  > calc_paths_ford(const vector< edge >& edges, size_t begin, size_t vert_nmb);

void zaitsev::shortest_paths_matrix(std::istream& in, std::ostream& out, const base_t& graphs)
{
  std::string graph_name;
  in >> graph_name;
  base_t::const_iterator it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
  }
  vector< vector< int > > adj_matrix = create_adjacency_matrix(it->second);
  vector< vector< int > > distances = calc_paths_floyd(adj_matrix);


  size_t max_int_len = std::to_string(std::numeric_limits< int >::lowest()).size();
  auto get_len = [](const std::pair< std::string, unit_t >& a)
    {
      return a.first.size();
    };
  auto need_to_extend = [&](const size_t len)
    {
      return len < max_int_len;
    };



  vector< size_t > names_length;
  std::transform(it->second.begin(), it->second.end(), std::back_inserter(names_length), get_len);
  size_t names_column_width = *(std::max_element(names_length.begin(), names_length.end()));
  std::replace_if(names_length.begin(), names_length.end(), need_to_extend, max_int_len);
  std::string names_indent(names_column_width, ' ');
  std::string indent(2, ' ');
  StreamGuard guard(out);

  out << names_indent;
  for (graph_t::const_iterator i = it->second.begin(); i != it->second.end(); ++i)
  {
    out << indent << i->first;
  }
  out << '\n';
  for (graph_t::const_iterator i = it->second.begin(); i != it->second.end(); ++i)
  {
    out << indent << i->first;
  }
  size_t i = 0;
  for (graph_t::const_iterator ii = it->second.begin(); ii != it->second.end(); ++ii)
  {
    out << std::left << std::setw(names_column_width) << ii->first;
    for (auto j : distances[i])
    {
      out << indent << std::left << std::setw(names_length[i]) << j;
    }
    out << '\n';
    ++ii;
  }
  return;
}

void zaitsev::check_negative_weight_cycles(std::istream& in, std::ostream& out, const base_t& graphs)
{
  std::string graph_name;
  in >> graph_name;
  base_t::const_iterator it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
  }
  vector< vector< int > > adj_matrix = create_adjacency_matrix(it->second);
  vector< vector< int > > distances = calc_paths_floyd(adj_matrix);
  bool negative_cycles = false;
  for (size_t i = 0; i < distances.size(); ++i)
  {
    if (distances[i][i] < 0)
    {
      negative_cycles = true;
      break;
    }
  }
  out << "Graph " << (negative_cycles ? "contains" : "doesn't contain") << " a negative weight cycle\n";
}

vector<vector<int>> create_adjacency_matrix(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  vector<vector<int>> matrix(graph.size(), vector<int>(graph.size(), inf));

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

vector< edge > extract_edges(const zaitsev::graph_t& graph)
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
  vector< edge > edges_list(edges_nmb);
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

std::pair<vector< int >, vector< size_t >  > calc_paths_ford(const vector< edge >& edges, size_t begin, size_t vert_nmb)
{
  vector< int > dist(vert_nmb, inf);
  dist[begin] = 0;
  vector< size_t > prev(vert_nmb, vert_nmb + 1);
  bool changed = true;
  size_t phase_nmb = 0;
  while (changed && phase_nmb < vert_nmb + 1)
  {
    for (size_t j = 0; j < edges.size(); ++j)
      if (dist[edges[j].a] < inf)
        if (dist[edges[j].b] > dist[edges[j].a] + edges[j].val)
        {
          dist[edges[j].b] = dist[edges[j].a] + edges[j].val;
          prev[edges[j].b] = edges[j].a;
          changed = true;
        }
  }
  if (phase_nmb == vert_nmb + 1)
  {
    std::fill(dist.begin(), dist.end(), inf);
  }

  return { dist, prev };
  /* if (d[t] == inf)
     cout << "No path from " << v << " to " << t << ".";
   else {
     vector<int> path;
     for (int cur = t; cur != -1; cur = p[cur])
       path.push_back(cur);
     reverse(path.begin(), path.end());

     cout << "Path from " << v << " to " << t << ": ";
     for (size_t i = 0; i < path.size(); ++i)
       cout << path[i] << ' ';
   }*/
}

vector< vector< int > > calc_paths_floyd(const vector< vector< int > >& matrix)
{
  vector<vector<int>> dist(matrix.size(), vector<int>(matrix.size(), inf));
  for (size_t k = 0; k < matrix.size(); ++k)
  {
    for (size_t i = 0; i < matrix.size(); ++i)
    {
      for (size_t j = 0; j < matrix.size(); ++j)
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
