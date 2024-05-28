#ifndef GRAPHS_BASE_HPP
#define GRAPHS_BASE_HPP
#include <iostream>
#include <map>
#include <string>

namespace zaitsev
{
  using unit_t = std::map< std::string, int >;
  using graph_t = std::map< std::string, unit_t >;
  using base_t = std::map <std::string, graph_t >;

  void create_graph(base_t& graphs, std::istream& in, std::ostream&);
  void delete_graph(base_t& graphs, std::istream& in, std::ostream&);
  void add_vertex(base_t& graphs, std::istream& in, std::ostream&);
  void add_edge(base_t& graphs, std::istream& in, std::ostream&);
  void merge_graphs(base_t& graphs, std::istream& in, std::ostream&);
}
#endif
