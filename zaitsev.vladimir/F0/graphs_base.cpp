#include "graphs_base.hpp"

void zaitsev::createGraph(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  if (graphs.find(args[1]) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + args[1] + "\", already exists.");
  }
  graphs[args[1]];
}

void zaitsev::deleteGraph(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  auto pos = graphs.find(args[1]);
  if (pos == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + args[1] + "\", doesn't exist.");
  }
  else
  {
    graphs.erase(pos);
  }
}

void zaitsev::addVertex(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = args[1];
  const std::string& vertex_name = args[2];
  auto it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("No graph \"" + graph_name + "\" in the base");
  }
  if (it->second.find(vertex_name) != it->second.end())
  {
    throw std::invalid_argument("Vertex \"" + vertex_name + "\" already exists");
  }
  it->second.insert({ vertex_name, unit_t{} });
}

void zaitsev::addEdge(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() > 6 || args.size() < 5 || (args.size() == 5 && args[1][0] == '-'))
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  bool check = false;
  if (args.size() == 6)
  {
    if (args[1] != "-check")
    {
      throw std::invalid_argument("Invalid option");
    }
    check = true;
  }
  const std::string& graph = (args.size() == 5 ? args[1] : args[2]);
  const std::string& begin = (args.size() == 5 ? args[2] : args[3]);
  const std::string& end = (args.size() == 5 ? args[3] : args[4]);
  int value = std::stoi(args.size() == 5 ? args[4] : args[5]);
  auto it_graph = graphs.find(graph);
  if (it_graph == graphs.end())
  {
    throw std::invalid_argument("Such graph doesn't found");
  }
  auto it_beg = it_graph->second.find(begin);
  if (it_beg != it_graph->second.end())
  {
    if (!check || (check && it_beg->second.find(end) == it_beg->second.end()))
    {
      it_beg->second[end] = value;
    }
    else
    {
      throw std::invalid_argument("Edge already exists");
    }
  }
  else
  {
    std::pair< std::string, unit_t > to_add = { begin, unit_t{} };
    to_add.second.insert({ end, value });
    it_graph->second.insert(std::move(to_add));
  }
  if (it_graph->second.find(end) == it_graph->second.end())
  {
    it_graph->second.insert({ end, unit_t{} });
  }
}

void zaitsev::mergeGraphs(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() > 5 || args.size() < 4 || (args.size() == 4 && args[1][0] == '-'))
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  bool check = false;
  if (args.size() == 5)
  {
    if (args[1] != "-check")
    {
      throw std::invalid_argument("Invalid option");
    }
    check = true;
  }
  const std::string& new_nm = (args.size() == 4 ? args[1] : args[2]);
  const std::string& nm_1 = (args.size() == 4 ? args[2] : args[3]);
  const std::string& nm_2 = (args.size() == 4 ? args[3] : args[4]);
  if (graphs.find(new_nm) != graphs.end() || graphs.find(nm_1) == graphs.end() || graphs.find(nm_2) == graphs.end())
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
        if (!check)
        {
          new_graph[i->first][j->first] = j->second;
        }
        else
        {
          if (new_graph[i->first].find(j->first) == new_graph[i->first].end())
          {
            new_graph[i->first][j->first] = j->second;
          }
          else
          {
            throw std::invalid_argument("Graphs have same edges and cannot be merged");
          }
        }
      }
    }
  }
  graphs.insert({ new_nm, new_graph });
  return;
}
