#ifndef I_O_PROCESSING_HPP
#define I_O_PROCESSING_HPP
#include <iostream>
#include "graphs_base.hpp"

namespace zaitsev
{
  void print_help();
  void init_base(const char* file, base_t& base);
  std::ostream& listGraphs(const base_t& graphs, std::istream& in, std::ostream&);
  std::ostream& printGraph(const base_t& graphs, std::istream& in, std::ostream& out);
  void readGraph(base_t& graphs, std::istream& in, std::ostream&);
  void writeGraph(const base_t& graphs, std::istream& in, std::ostream&);
  void dump(const base_t& graphs, std::istream& in, std::ostream&);
}
#endif
