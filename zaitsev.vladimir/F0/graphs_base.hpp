#ifndef GRAPHS_BASE_HPP
#define GRAPHS_BASE_HPP
#include <istream>
#include <map>
#include <string>

namespace zaitsev
{
  using unit_t = std::map< std::string, int >;
  using graph_t = std::map< std::string, unit_t >;
  using base_t = std::map <std::string, graph_t >;

  void create_graph(std::istream& in, base_t& graphs);
  void delete_graph(base_t& graphs, const std::string& graph_name);
  void add_vertex(base_t& graphs, const std::string& graph_name, const std::string& vertex_name);
  void add_edge(std::istream& in, base_t& graphs);
  void merge_graphs(std::istream& in, base_t& graphs);
}
#endif
