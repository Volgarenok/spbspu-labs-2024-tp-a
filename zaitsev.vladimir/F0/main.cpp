#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <string.h>
#include <stream_guard.hpp>

using unit_t = std::map< std::string, int >;
using graph_t = std::map< std::string, unit_t >;
using base_t = std::map <std::string, graph_t >;

void create_graph(base_t& graphs, const std::string& new_graph_name)
{
  if (graphs.find(new_graph_name) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + new_graph_name + "\", already exists.");
  }
  graphs[new_graph_name];
}

void delete_graph(base_t& graphs, const std::string& graph_name)
{
  auto pos = graphs.find(graph_name);
  if (pos == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exist.");
  }
  else
  {
    graphs.erase(pos);
  }
}

std::ostream& list_of_graphs(std::ostream& out, base_t& graphs)
{
  if (graphs.empty())
  {
    return out << "No saved graphs\n";
  }
//  zaitsev::StreamGuard guard(out);
  auto c_it = graphs.cbegin();
  for (size_t i = 0; i < graphs.size(); ++i)
  {
    out << std::setw(3) << i << ". ";
    out << c_it->first << '\n';
  }
  return out;
}

void print_help()
{
  using namespace std;
  string indent(2, ' ');
  cout << "Help:\n";
  cout << "1.  read <file> <graph-name>\n" << indent;
  cout << "Read the graph from the file <file>, and assign it the name <graph-name>.\n\n";
  cout << "2.  write <graph> <file>\n" << indent;
  cout << "Write a graph <graph>  to a file <file>.\n\n";
  cout << "3.  list_of_graphs\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n";
  cout << "4.  print <graph-name>\n" << indent;
  cout << "Print a description of the graph <graph-name>.\n\n";
  cout << "5.  create_graph <graph-name>\n" << indent;
  cout << "Create an empty graph named <graph-name>.\n\n";
  cout << "6.  delete_graph <graph>\n" << indent;
  cout << "Delete a graph named <graph-name>.\n\n";
  cout << "7.  add_vertex <graph> <vertex>  \n" << indent;
  cout << "Add a vertex <vertex> to the graph <graph-name>.\n\n";
  cout << "8.  add_edge [-check] <graph> <begin> <end> <value>\n" << indent;
  cout << "Add an edge to the graph <graph> that connects the vertices <begin> <end> with the value <value>.\n\n";
  cout << "9.  merge [-check] <new-graph> <graph-1> <graph-2> \n" << indent;
  cout << "A new graph <new-graph> is created, which is a union of graphs <graph-1> and <graph-2>.\n\n";
  cout << "10. negative_weight_cycles <graph>\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n"; //to do
  cout << "11. shortest <graph> <begin> <end>\n" << indent;
  cout << "Calculate the length of the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "12. shortest_trace <graph> <vertex-begin> <vertex-end>\n" << indent;
  cout << "Print the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "13. shortest_path_matrix <graph>\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n"; //to do
  cout << "14. dump <file>\n" << indent;
  cout << "Create a file <file> in which all graphs saved in the program are written.\n\n";

  return;
}

std::ostream& print_graph(std::ostream& out, base_t& graphs, const std::string& graph_name)
{
  base_t::iterator graph = graphs.find(graph_name);
  if (graph != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
  }
  out << "Graph \"" << graph_name << "\":";
  out << ">Verteces of graph \"" << graph_name << "\":\n";
  for (graph_t::iterator i = graph->second.begin(); i != graph->second.end(); ++i)
  {
    out << "  " << i->first << "\n";
  }
  out << ">Edges of graph\n";
  for (graph_t::iterator i=graph->second.begin();i!= graph->second.end();++i)
  {
    for (unit_t::iterator j=i->second.begin();j!=i->second.end();++j)
    {
      out << "  " << i->first << " -> " << j->first << ": " << j->second << '\n';
    }
  }
  return out;
}

int main(int argc, char** argv)
{
  base_t graphs;

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
  if (argc == 2)
  {
    std::ofstream in(argv[1]);
    if (!in)
    {

    }
    else
    {

    }
  }




 }
