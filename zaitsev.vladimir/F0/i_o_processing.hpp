#ifndef I_O_PROCESSING_HPP
#define I_O_PROCESSING_HPP
#include <iostream>
#include "graphs_base.hpp"

namespace zaitsev
{
  void print_help();
  void init_base(const char* file, base_t& base);
  std::ostream& list_of_graphs(std::ostream& out, base_t& graphs);
  std::ostream& print_graph(std::istream& in, std::ostream& out, const base_t& graphs);
  void read_graph(std::istream& in, base_t& graphs);
  void dump(const base_t& graphs);
}
#endif
