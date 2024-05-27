#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <string.h>
#include <experimental/filesystem>
#include <delimiter.hpp>
#include <stream_guard.hpp>
#include "i_o_processing.hpp"

using unit_t = std::map< std::string, int >;
using graph_t = std::map< std::string, unit_t >;
using base_t = std::map <std::string, graph_t >;

graph_t basic_graph_read(std::istream& in)
{
  using namespace zaitsev;
  StreamGuard guard(in);
  size_t vertices_nmb = 0;
  graph_t new_graph;
  in >> Delimiter{ "Vertiñes" } >> Delimiter{ "(" } >> vertices_nmb >> Delimiter{ "):" };
  std::string vert_name;
  for (size_t i = 0; i < vertices_nmb; ++i)
  {
    in >> vert_name;
    if (!in)
    {
      throw std::exception("");
    }
    new_graph.insert({ vert_name, unit_t{} });
  }
  size_t edges_nmb = 0;
  in >> Delimiter{ "Edges" } >> Delimiter{ "(" } >> edges_nmb >> Delimiter{ "):" };
  for (size_t i = 0; i < edges_nmb; ++i)
  {
    std::string begin, end;
    int value;
    in >> begin >> Delimiter{ "-->" } >> end >> value;
    if (!in)
    {
      throw std::exception("");
    }
    new_graph[begin].insert({ end, value });
  }
  return new_graph;
}

void init_base(const char* file, base_t& base)
{
  if (!std::experimental::filesystem::exists(file))
  {
    throw std::invalid_argument("Initial file does't found");
  }
  std::ifstream in(file);
  using namespace zaitsev;
  StreamGuard guard(in);
  size_t graphs_nmb = 0;
  in >> std::noskipws >> Delimiter{ "Graphs number -" } >> std::skipws >> graphs_nmb;
  if (!in)
  {
    throw std::invalid_argument("");
  }
  for (size_t i = 0; i < graphs_nmb; ++i)
  {
    std::string graph_name;
    in >> std::noskipws >> Delimiter{ "Graph name :" } >> std::skipws >> graph_name;
    base.insert({ graph_name, basic_graph_read(in) });
  }
  return;
}

//void basic_graph_print(std::ostream& out, const graph_t& graph, size_t indnent_sz = 2)
//{
//  std::string indent(indnent_sz, ' ');
//  out << "Vertiñes (" << graph.size() << "):\n";
//  size_t counter = 0;
//  for (graph_t::const_iterator it = graph.cbegin(); it != graph.cend(); ++it)
//  {
//    out << indent << it->first << '\n';
//    counter += it->second.size();
//  }
//  out << "Edges (" << counter << "):\n";
//  for (graph_t::const_iterator it_g = graph.cbegin(); it_g != graph.cend(); ++it_g)
//  {
//    for (unit_t::const_iterator it_v = it_g->second.cbegin(); it_v != it_g->second.cbegin(); ++it_v)
//    {
//      out << indent << it_g->first << " --> " << it_v->first << " : " << it_v->second << '\n';
//    }
//  }
//}
//
//std::ostream& print_graph(std::istream& in, std::ostream& out, base_t& graphs, const std::string& graph_name)
//{
//  base_t::iterator graph = graphs.find(graph_name);
//  if (graph != graphs.end())
//  {
//    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
//  }
//  out << "Graph name: " << graph->first << '\n';
//  basic_graph_print(out, graph->second);
//  return out;
//}


int main(int argc, char** argv)
{
  using namespace zaitsev;
  base_t graphs;

  if (argc > 3)
  {
    std::cerr << "Invalid number of arguments\n";
  }
  if (argc != 2 && argc != 3)
  {
    std::cout << "Created empty base\n";
  }
  if (argc == 2)
  {
    if (argv[1][0] == '-' && strcmp(argv[1], "-help"))
    {
      std::cerr << "Invalid oprion\n";
    }
    if (!strcmp(argv[1], "-help"))
    {
      print_help();
    }
  }


  switch (argc)
  {
  case 2:
    if (!strcmp(argv[1], "-help"))
    {
      print_help();
    }
    else
    {
      if (std::experimental::filesystem::exists(argv[1]))
      {

      }
    }
    break;
  case 3:
    if (!strcmp(argv[1], "--help"))
    {
      print_help();
    }
    return 1;
  default:
    std::cout << "Empty base was created\n";
  }
  if (argc == 3)
  {
    if (!strcmp(argv[1], "--help"))
    {
      print_help();
    }
    else
    {
      std::cerr << "Invalid option selected\n";
    }
  /*  std::ofstream in(argv[2]);
    if (!in)
    {

    }
    else
    {

    }*/
  }





 }
