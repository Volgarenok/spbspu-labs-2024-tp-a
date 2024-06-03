#include <iostream>
#include <functional>
#include <string>
#include <map>
#include "i_o_processing.hpp"
#include "path_search.hpp"

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
          printHelp();
        }
        else
        {
          std::cerr << "Invalid option\n";
        }
      }
      else
      {
        initBase(argv[1], graphs);
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
        printHelp();
      }
      initBase(argv[2], graphs);
    }
  }
  catch (const std::exception& e)
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
    commands["listgraphs"] = std::bind(listGraphs, std::cref(graphs), _1, _2);
    commands["print"] = std::bind(printGraph, std::cref(graphs), _1, _2);
    commands["creategraph"] = std::bind(createGraph, std::ref(graphs), _1, _2);
    commands["deletegraph"] = std::bind(deleteGraph, std::ref(graphs), _1, _2);
    commands["addvertex"] = std::bind(addVertex, std::ref(graphs), _1, _2);
    commands["addedge"] = std::bind(addEdge, std::ref(graphs), _1, _2);
    commands["merge"] = std::bind(mergeGraphs, std::ref(graphs), _1, _2);
    commands["negativeweightcycles"] = std::bind(checkNegativeWeightCycles, std::cref(graphs), _1, _2);
    commands["shortestdistance"] = std::bind(findShortestDistance, std::cref(graphs), _1, _2);
    commands["shortesttrace"] = std::bind(findShortestPathTtrace, std::cref(graphs), _1, _2);
    commands["shortestpathmatrix"] = std::bind(printShortestPathsMatrix, std::cref(graphs), _1, _2);
    commands["dump"] = std::bind(dump, std::ref(graphs), _1, _2);
  }
  std::vector< std::string > args;
  while (!std::cin.eof())
  {
    std::cout << "command: ";
    readArgs(std::cin, args);
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
        throw std::invalid_argument("Invalid command.");
      }
      cmd_it->second(args, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << '\n';
    }
    if (std::cin.fail())
    {
      std::cin.clear();
    }
  }
  return 0;
}
