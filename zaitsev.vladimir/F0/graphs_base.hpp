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

  void createGraph(base_t& graphs, std::istream& in, std::ostream&);
  void deleteGraph(base_t& graphs, std::istream& in, std::ostream&);
  void addVertex(base_t& graphs, std::istream& in, std::ostream&);
  void addEdge(base_t& graphs, std::istream& in, std::ostream&);
  void mergeGraphs(base_t& graphs, std::istream& in, std::ostream&);
}
#endif
