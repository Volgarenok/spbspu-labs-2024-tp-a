#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <functional>
#include <iomanip>
#include <string>
#include <map>
#include <string.h>
#include <delimiter.hpp>
#include <stream_guard.hpp>
#include "i_o_processing.hpp"
#include "path_search.hpp"

using unit_t = std::map< std::string, int >;
using graph_t = std::map< std::string, unit_t >;
using base_t = std::map <std::string, graph_t >;

int main(int argc, char** argv)
{
  using namespace zaitsev;
  base_t graphs;

  if (argc > 3)
  {
    std::cerr << "Invalid number of arguments\n";
  }
  try
  {
    if (argc == 2)
    {
      if (argv[1][0] == '-' && strcmp(argv[1], "-help"))
      {
        std::cerr << "Invalid option\n";
        init_base(argv[1], graphs);
      }
      if (!strcmp(argv[1], "-help"))
      {
        print_help();
      }
    }
    if (argc == 3)
    {
      if (strcmp(argv[1], "-help"))
      {
        std::cerr << "Invalid option\n";
      }
      else
      {
        print_help();
      }
      init_base(argv[2], graphs);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream& out)> > commands;
  {
    using namespace std::placeholders;
    commands["read"] = std::bind(read_graph, std::ref(graphs), _1, _2);
    commands["write"] = std::bind(write_graph, std::cref(graphs), _1, _2);
    commands["list_of_graphs"] = std::bind(list_of_graphs, std::cref(graphs), _1, _2);
    commands["print "] = std::bind(print_graph, std::cref(graphs), _1, _2);
    commands["create_graph"] = std::bind(create_graph, std::ref(graphs), _1, _2);
    commands["delete_graph"] = std::bind(delete_graph, std::ref(graphs), _1, _2);
    commands["add_vertex"] = std::bind(add_vertex, std::ref(graphs), _1, _2);
    commands["add_edge"] = std::bind(add_edge, std::ref(graphs), _1, _2);
    commands["merge"] = std::bind(merge_graphs, std::ref(graphs), _1, _2);
    commands["negative_weight_cycles"] = std::bind(check_negative_weight_cycles, std::cref(graphs), _1, _2);
    commands["shortest_distance"] = std::bind(shortest_path, std::cref(graphs), _1, _2);
    commands["shortest_trace"] = std::bind(shortest_path_trace, std::cref(graphs), _1, _2);
    commands["shortest_path_matrix"] = std::bind(shortest_paths_matrix, std::cref(graphs), _1, _2);
    commands["dump"] = std::bind(dump, std::ref(graphs), _1, _2);
  }
  while (!std::cin.eof())
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
