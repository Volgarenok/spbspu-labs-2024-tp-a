#ifndef I_O_PROCESSING_HPP
#define I_O_PROCESSING_HPP
#include <iostream>
#include "graphs_base.hpp"

namespace zaitsev
{
  void print_help();
  void init_base(const char* file, base_t& base);
  std::ostream& list_of_graphs(const base_t& graphs, std::istream& in, std::ostream&);
  std::ostream& print_graph(const base_t& graphs, std::istream& in, std::ostream& out);
  void read_graph(base_t& graphs, std::istream& in, std::ostream&);
  void write_graph(const base_t& graphs, std::istream& in, std::ostream&);
  void dump(const base_t& graphs, std::istream& in, std::ostream&);
}
#endif
