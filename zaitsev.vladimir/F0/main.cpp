#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <map>
#include <limits>
#include <delimiter.hpp>
#include <stream_guard.hpp>
#include "i_o_processing.hpp"
#include "path_search.hpp"

using unit_t = std::map< std::string, int >;
using graph_t = std::map< std::string, unit_t >;
using base_t = std::map<std::string, graph_t >;

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
      if (argv[1][0] == '-')
      {
        if (std::string(argv[1]) == "--help")
        {
          print_help();
        }
        else
        {
          std::cerr << "Invalid option\n";
        }
      }
      else
      {
        init_base(argv[1], graphs);
      }
    }
    if (argc == 3)
    {
      if (std::string(argv[1]) != "--help")
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
  if (graphs.empty())
  {
    std::cout << "Created empty base.\n";
  }
  std::map< std::string, std::function< void(const std::vector< std::string >&, std::ostream& out) > > commands;
  {
    using namespace std::placeholders;
    commands["read"] = std::bind(readGraph, std::ref(graphs), _1, _2);
    commands["write"] = std::bind(writeGraph, std::cref(graphs), _1, _2);
    commands["list_graphs"] = std::bind(listGraphs, std::cref(graphs), _1, _2);
    commands["print"] = std::bind(printGraph, std::cref(graphs), _1, _2);
    commands["create_graph"] = std::bind(createGraph, std::ref(graphs), _1, _2);
    commands["delete_graph"] = std::bind(deleteGraph, std::ref(graphs), _1, _2);
    commands["add_vertex"] = std::bind(addVertex, std::ref(graphs), _1, _2);
    commands["add_edge"] = std::bind(addEdge, std::ref(graphs), _1, _2);
    commands["merge"] = std::bind(mergeGraphs, std::ref(graphs), _1, _2);
    commands["negative_weight_cycles"] = std::bind(checkNegativeWeightCycles, std::cref(graphs), _1, _2);
    commands["shortest_distance"] = std::bind(findShortestDistance, std::cref(graphs), _1, _2);
    commands["shortest_trace"] = std::bind(findShortestPathTtrace, std::cref(graphs), _1, _2);
    commands["shortest_path_matrix"] = std::bind(printShortestPathsMatrix, std::cref(graphs), _1, _2);
    commands["dump"] = std::bind(dump, std::ref(graphs), _1, _2);
  }
  std::vector< std::string > args;
  while (!std::cin.eof())
  {
    std::cout << "command: ";
    read_args(std::cin, args);
    if (!std::cin)
    {
      break;
    }
    try
    {
      auto cmd_it = commands.find(args[0]);
      if (cmd_it == commands.end())
      {
        std::cin.setstate(std::ios::failbit);
        throw std::invalid_argument("Invalid command");
      }
      cmd_it->second(args, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    if (std::cin.fail())
    {
      std::cin.clear();
    }
  }
  return 0;
}
