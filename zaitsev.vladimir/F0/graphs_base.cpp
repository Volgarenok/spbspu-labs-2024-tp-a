#include "graphs_base.hpp"

void zaitsev::create_graph(base_t& graphs, std::istream& in, std::ostream&)
{
  std::string new_graph_name;
  in >> new_graph_name;
  if (graphs.find(new_graph_name) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + new_graph_name + "\", already exists.");
  }
  graphs[new_graph_name];
}

void zaitsev::delete_graph(base_t& graphs, std::istream& in, std::ostream&)
{
  std::string del_name;
  in >> del_name;
  auto pos = graphs.find(del_name);
  if (pos == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + del_name + "\", doesn't exist.");
  }
  else
  {
    graphs.erase(pos);
  }
}

void zaitsev::add_vertex(base_t& graphs, std::istream& in, std::ostream&)
{
  std::string graph_name;
  std::string vertex_name;
  in >> graph_name >> vertex_name;
  auto it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("No graph \"" + graph_name + "\" in the base.");
  }
  if (it->second.find(vertex_name) != it->second.end())
  {
    throw std::invalid_argument("Vertex \"" + vertex_name + "\" already exists.");
  }
  it->second.insert({ vertex_name, unit_t{} });
}

void zaitsev::add_edge(base_t& graphs, std::istream& in, std::ostream&)
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
  if (!check)
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
    throw std::invalid_argument("Input error");
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

void zaitsev::merge_graphs(base_t& graphs, std::istream& in, std::ostream&)
{
  std::string option;
  std::string new_nm;
  std::string nm_1;
  std::string nm_2;
  in >> option;
  if (option == "-check")
  {
    in >> new_nm;
  }
  else
  {
    new_nm = std::move(option);
  }
  in >> nm_1 >> nm_2;
  if (new_nm == nm_1 || new_nm == nm_2 || graphs.find(nm_1) == graphs.end() || graphs.find(nm_2) == graphs.end())
  {
    throw std::invalid_argument("Invalid arguments");
  }
  graph_t new_graph = graphs.find(nm_2)->second;
  graph_t graph_1_inst = graphs.find(nm_1)->second;

  for (graph_t::const_iterator i = graph_1_inst.begin(); i != graph_1_inst.end(); ++i)
  {
    graph_t::iterator same_vert = new_graph.find(i->first);
    if (same_vert == new_graph.end())
    {
      new_graph.insert({ *i });
    }
    else
    {
      for (unit_t::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
      {
        new_graph[i->first][j->first] = j->second;
      }
    }
  }
  graphs.insert({ new_nm, new_graph });
  return;
}
