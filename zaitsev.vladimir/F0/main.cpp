#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

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

std::ostream& print(std::ostream& out, base_t& graphs, const std::string& graph_name)
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

}
