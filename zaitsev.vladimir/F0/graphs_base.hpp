#ifndef GRAPHS_BASE_HPP
#define GRAPHS_BASE_HPP
#include <ostream>
#include <map>
#include <vector>
#include <string>

namespace zaitsev
{
  using unit_t = std::map< std::string, int >;
  using graph_t = std::map< std::string, unit_t >;
  using base_t = std::map < std::string, graph_t >;

  void createGraph(base_t& graphs, const std::vector< std::string >& args, std::ostream&);
  void deleteGraph(base_t& graphs, const std::vector< std::string >& args, std::ostream&);
  void addVertex(base_t& graphs, const std::vector< std::string >& args, std::ostream&);
  void addEdge(base_t& graphs, const std::vector< std::string >& args, std::ostream&);
  void mergeGraphs(base_t& graphs, const std::vector< std::string >& args, std::ostream&);
}
#endif
