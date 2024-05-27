#include "graphs_base.hpp"

void zaitsev::create_graph(base_t& graphs, const std::string& new_graph_name)
{
  if (graphs.find(new_graph_name) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + new_graph_name + "\", already exists.");
  }
  graphs[new_graph_name];
}

void zaitsev::delete_graph(base_t& graphs, const std::string& graph_name)
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

void zaitsev::add_vertex(base_t& graphs, const std::string& graph_name, const std::string& vertex_name)
{
  auto it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("No graph " + graph_name + " in the base.");
  }
  it->second.insert({ vertex_name, unit_t{} });
}

void zaitsev::add_edge(std::istream& in, base_t& graphs)
{
  std::string option, graph, begin, end;
  int value = 0;
  bool check = false;
  in >> option;
  if (option[0] == '-')
  {
    if (option != "-check")
    {
      throw std::invalid_argument("Invalid option");
    }
    check = true;
  }
  if (check)
  {
    graph = std::move(option);
    in >> begin >> end >> value;
  }
  else
  {
    in >> graph >> begin >> end >> value;
  }
  if (!in)
  {
    throw std::invalid_argument("Invalid arguments");
  }
  auto it_graph = graphs.find(graph);
  if (it_graph == graphs.end())
  {
    throw std::invalid_argument("Such graph doesn't found");
  }
  auto it_vertex = it_graph->second.find(begin);
  if (it_vertex != it_graph->second.end())
  {
    it_vertex->second.insert({ end, value });
  }
  else
  {
    auto it_vertex = it_graph->second.insert({ begin, unit_t{} });
    it_vertex.first->second.insert({ end, value });
  }
  if (it_graph->second.find(end) == it_graph->second.end())
  {
    it_graph->second.insert({ end, unit_t{} });
  }
}
