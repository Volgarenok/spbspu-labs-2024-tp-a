#include "graphs_base.hpp"

void zaitsev::create_graph(std::istream& in, base_t& graphs)
{
  std::string new_graph_name;
  in >> new_graph_name;
  if (graphs.find(new_graph_name) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + new_graph_name + "\", already exists.");
  }
  graphs[new_graph_name];
}

void zaitsev::delete_graph(std::istream& in, base_t& graphs)
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

void zaitsev::add_vertex(std::istream& in, base_t& graphs)
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

void zaitsev::merge_graphs(std::istream& in, base_t& graphs)
{
  std::string option;
  std::string new_name;
  std::string name_1;
  std::string name_2;
  in >> option;
//  bool check = false;
  if (option == "-check")
  {
 //   check = true;
    in >> new_name;
  }
  else
  {
    new_name = std::move(option);
  }
  in >> name_1 >> name_2;
  if (new_name == name_1 || new_name == name_2 || graphs.find(name_1) == graphs.end() || graphs.find(name_2) == graphs.end())
  {
    throw std::invalid_argument("Invalid arguments");
  }
  graph_t temp = graphs.find(name_2)->second;
  graph_t graph_1_inst = graphs.find(name_1)->second;

  for (graph_t::const_iterator i = graph_1_inst.cbegin(); i != graph_1_inst.cend(); ++i)
  {
    graph_t::iterator to_merge = temp.find(i->first);
    if (temp.find(i->first) == temp.end())
    {
      temp.insert({ *i });
    }
    else
    {
      for (unit_t::iterator j = to_merge->second.begin(); j != to_merge->second.end(); ++j)
      {
        temp[i->first][j->first] = j->second;
      }
    }
  }
  graphs.insert({ new_name, temp });
}
