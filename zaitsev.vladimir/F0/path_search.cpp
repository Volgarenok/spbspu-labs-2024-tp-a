#include "path_search.hpp"
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stream_guard.hpp>

using std::forward_list;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;

constexpr int inf = std::numeric_limits< int >::max();

struct edge
{
  size_t a;
  size_t b;
  int val;
};

unordered_map< string, size_t > convertToIndexes(const zaitsev::graph_t& graph);
vector< vector<int> > createAdjacencyMatrix(const zaitsev::graph_t& graph);
vector< edge > extractEdges(const zaitsev::graph_t& graph);
vector< vector< int > > calcPathsFloyd(const zaitsev::graph_t& graph);
pair< vector< int >, vector< size_t > > calcPathsFord(const vector< edge >& edges, size_t begin, size_t vert_nmb);

void zaitsev::findShortestDistance(const base_t& graphs, const vector< string >& args, std::ostream& out)
{
  if (args.size() != 4)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = args[1];
  const std::string& begin_name = args[2];
  const std::string& end_name = args[3];
  base_t::const_iterator graph_pos = graphs.find(graph_name);
  if (graph_pos == graphs.end())
  {
    throw std::invalid_argument("Graph doesn't exist");
  }
  graph_t::const_iterator graph_beg = graph_pos->second.find(begin_name);
  graph_t::const_iterator graph_end = graph_pos->second.find(end_name);
  if (graph_beg == graph_pos->second.end() || graph_end == graph_pos->second.end())
  {
    throw std::invalid_argument("Vertex doesn't exist");
  }
  unordered_map< string, size_t > indexes = convertToIndexes(graph_pos->second);
  vector< edge > edges = extractEdges(graph_pos->second);
  pair< vector< int >, vector< size_t > > dist_with_prev = calcPathsFord(edges, indexes[begin_name], indexes.size());

  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    throw std::invalid_argument("Graph contains negative weight cycles");
  }
  if (dist_with_prev.first[indexes[end_name]] == inf)
  {
    throw std::invalid_argument("End vertex cannot be reached");
  }
  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    out << "Vertex \"" << end_name << "\" is unreachable from \"" << begin_name << "\".\n";
  }
  else
  {
    out << dist_with_prev.first[indexes[end_name]] << '\n';
  }
  return;
}

void zaitsev::findShortestPathTtrace(const base_t& graphs, const vector< string >& args, std::ostream& out)
{
  if (args.size() != 4)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = args[1];
  const std::string& begin_name = args[2];
  const std::string& end_name = args[3];
  base_t::const_iterator graph_pos = graphs.find(graph_name);
  if (graph_pos == graphs.end())
  {
    throw std::invalid_argument("Graph doesn't exist");
  }
  const graph_t& graph = graph_pos->second;
  if (graph.find(begin_name) == graph.end() || graph.find(end_name) == graph.end())
  {
    throw std::invalid_argument("Vertex doesn't exist");
  }
  unordered_map< string, size_t > indexes = convertToIndexes(graph);
  vector< edge > edges = extractEdges(graph);
  pair< vector< int >, vector< size_t > > dist_with_prev = calcPathsFord(edges, indexes[begin_name], indexes.size());

  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    throw std::invalid_argument("Graph contains negative weight cycles");
  }
  if (dist_with_prev.first[indexes[end_name]] == inf)
  {
    throw std::invalid_argument("End vertex cannot be reached");
  }
  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    out << "Vertex \"" << end_name << "\" is unreachable from \"" << begin_name << "\".\n";
  }
  else
  {
    forward_list< string >path = { end_name };
    size_t i = indexes[end_name];
    while (path.front() != begin_name)
    {
      i = dist_with_prev.second[i];
      path.push_front(std::next(graph.begin(), i)->first);
    }
    out << path.front();
    for (auto i = ++path.begin(); i != path.end(); ++i)
    {
      out << "->" << *i;
    }
    out << '\n';
  }
  return;
}

void zaitsev::printShortestPathsMatrix(const base_t& graphs, const vector< string >& args, std::ostream& out)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  base_t::const_iterator it = graphs.find(args[1]);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + args[1] + "\", doesn't exists.");
  }
  if (it->second.empty())
  {
    out << "Graph is empty.\n";
    return;
  }
  vector< vector< int > > distances = calcPathsFloyd(it->second);
  size_t max_int_len = std::to_string(std::numeric_limits< int >::lowest()).size();
  auto get_len = [](const std::pair< string, unit_t >& a)
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
  string names_indent(names_column_width, ' ');
  string indent(2, ' ');
  StreamGuard guard(out);

  out << names_indent;
  size_t i = 0;
  for (graph_t::const_iterator ii = it->second.begin(); ii != it->second.end(); ++ii)
  {
    out << indent << std::left << std::setw(names_length[i]) << ii->first;
  }
  out << '\n';
  i = 0;
  for (graph_t::const_iterator ii = it->second.begin(); ii != it->second.end(); ++ii)
  {
    out << std::left << std::setw(names_column_width) << ii->first;
    for (auto j : distances[i])
    {
      if (j == inf)
      {
        out << indent << std::left << std::setw(names_length[i]) << "inf";
      }
      else
      {
        out << indent << std::left << std::setw(names_length[i]) << j;
      }
    }
    out << '\n';
    ++i;
  }
  return;
}

void zaitsev::checkNegativeWeightCycles(const base_t& graphs, const vector< string >& args, std::ostream& out)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  base_t::const_iterator it = graphs.find(args[1]);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + args[1] + "\", doesn't exists.");
  }
  vector< vector< int > > distances = calcPathsFloyd(it->second);
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

unordered_map< string, size_t > convertToIndexes(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  unordered_map< string, size_t > vert_indexes(graph.size());
  size_t index = 0;
  for (graph_t::const_iterator i = graph.begin(); i != graph.end(); ++i, ++index)
  {
    vert_indexes[i->first] = index;
  }
  return vert_indexes;
}

vector< vector< int > > createAdjacencyMatrix(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  vector< vector< int > > matrix(graph.size(), vector< int >(graph.size(), inf));
  unordered_map< string, size_t > vert_indexes = convertToIndexes(graph);

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

vector< edge > extractEdges(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;

  unordered_map< string, size_t > vert_indexes = convertToIndexes(graph);
  size_t edges_nmb = 0;
  for (graph_t::const_iterator i = graph.begin(); i != graph.end(); ++i)
  {
    edges_nmb += i->second.size();
  }
  vector< edge > edges_list(edges_nmb);
  size_t i = 0, k = 0;
  for (graph_t::const_iterator it_i = graph.begin(); it_i != graph.end(); ++it_i)
  {
    for (unit_t::const_iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
    {
      edges_list[k] = { i, vert_indexes[it_j->first], it_j->second };
      ++k;
    }
    ++i;
  }
  return edges_list;
}

pair< vector< int >, vector< size_t > > calcPathsFord(const vector< edge >& edges, size_t begin, size_t vert_nmb)
{
  vector< int > dist(vert_nmb, inf);
  dist[begin] = 0;
  vector< size_t > prev(vert_nmb, vert_nmb + 1);
  bool changed = true;
  size_t phase_nmb = 0;
  while (changed && phase_nmb < vert_nmb + 1)
  {
    changed = false;
    for (size_t j = 0; j < edges.size(); ++j)
    {
      if (dist[edges[j].a] < inf && dist[edges[j].b] > dist[edges[j].a] + edges[j].val)
      {
        dist[edges[j].b] = dist[edges[j].a] + edges[j].val;
        prev[edges[j].b] = edges[j].a;
        changed = true;
      }
    }
    ++phase_nmb;
  }
  if (phase_nmb == vert_nmb + 1)
  {
    std::fill(dist.begin(), dist.end(), inf);
  }

  return { dist, prev };
}

vector< vector< int > > calcPathsFloyd(const zaitsev::graph_t& graph)
{
  vector< vector< int > > dist = createAdjacencyMatrix(graph);
  for (size_t k = 0; k < dist.size(); ++k)
  {
    for (size_t i = 0; i < dist.size(); ++i)
    {
      for (size_t j = 0; j < dist.size(); ++j)
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
