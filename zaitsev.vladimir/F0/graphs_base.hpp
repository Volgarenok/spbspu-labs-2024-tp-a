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
  void delete_graph(std::istream& in, base_t& graphs);
  void add_vertex(std::istream& in, base_t& graphs);
  void add_edge(std::istream& in, base_t& graphs);
  void merge_graphs(std::istream& in, base_t& graphs);
}
#endif
