#include "i_o_processing.hpp"
#include <fstream>
#include <string>
#include <iomanip>
#include <delimiter.hpp>

zaitsev::graph_t basicGraphRead(std::istream& in);
void basicGraphPrint(std::ostream& out, const zaitsev::graph_t& graph, size_t indnent_sz = 2);

std::ostream& zaitsev::listGraphs(const base_t& graphs, const std::vector< std::string >&, std::ostream& out)
{
  if (graphs.empty())
  {
    return out << "No saved graphs\n";
  }
  auto c_it = graphs.cbegin();
  for (size_t i = 1; i < graphs.size() + 1; ++i)
  {
    out << i << ". " << c_it->first << '\n';
    ++c_it;
  }
  return out;
}

void zaitsev::readArgs(std::istream& in, std::vector< std::string >& dest_args)
{
  std::string raw_args;
  dest_args.clear();
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }
  std::getline(in, raw_args);
  raw_args += ' ';
  size_t beg = raw_args.size();
  for (size_t i = 0; i < raw_args.size(); ++i)
  {
    if (raw_args[i] != ' ')
    {
      beg = (beg == raw_args.size() ? i : beg);
    }
    else
    {
      if (beg != raw_args.size())
      {
        dest_args.push_back(raw_args.substr(beg, i - beg));
      }
      beg = raw_args.size();
    }
  }
  return;
}

void zaitsev::printHelp()
{
  using namespace std;
  string indent(2, ' ');
  cout << "Help:\n";
  cout << "1. read <file> <graph>\n" << indent;
  cout << "Read the graph from the file <file>, and assign it the name <graph>.\n\n";
  cout << "2. write <graph> <file>\n" << indent;
  cout << "Write a graph <graph> to a file <file>.\n\n";
  cout << "3. listgraphs\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n";
  cout << "4. print <graph>\n" << indent;
  cout << "Print a description of the graph <graph>.\n\n";
  cout << "5. creategraph <graph>\n" << indent;
  cout << "Create an empty graph named <graph>.\n\n";
  cout << "6. deletegraph <graph>\n" << indent;
  cout << "Delete a graph named <graph>.\n\n";
  cout << "7. addvertex <graph> <vertex> \n" << indent;
  cout << "Add a vertex <vertex> to the graph <graph>.\n\n";
  cout << "8. addedge [-check] <graph> <begin> <end> <value>\n" << indent;
  cout << "Add an edge to the graph <graph> that connects the vertices <begin> <end> with the value <value>.\n\n";
  cout << "9. merge [-check] <new-graph> <graph-1> <graph-2> \n" << indent;
  cout << "A new graph <new-graph> is created, which is a union of graphs <graph-1> and <graph-2>.\n\n";
  cout << "10. negativeweightcycles <graph>\n" << indent;
  cout << "Display a message about the presence/absence of a negative weight cycle in graph.\n\n";
  cout << "11. shortestdistance <graph> <begin> <end>\n" << indent;
  cout << "Calculate the length of the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "12. shortesttrace <graph> <begin> <end>\n" << indent;
  cout << "Print the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "13. shortestpathmatrix <graph>\n" << indent;
  cout << "Output the matrix of shortest paths between all vertices.\n\n";
  cout << "14. dump <file>\n" << indent;
  cout << "Create a file <file> in which all graphs saved in the program are written.\n\n";
  return;
}

std::ostream& zaitsev::printGraph(const base_t& graphs, const std::vector< std::string >& args, std::ostream& out)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  base_t::const_iterator graph = graphs.find(args[1]);
  if (graph == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + args[1] + "\" doesn't exists.");
  }
  out << "Graph name: " << graph->first << '\n';
  basicGraphPrint(out, graph->second);
  return out;
}

void zaitsev::dump(const base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  if (std::ifstream(args[1]).good())
  {
    throw std::invalid_argument("File already exists");
  }

  std::ofstream out(args[1]);
  out << "Graphs number: " << graphs.size() << '\n';
  for (base_t::const_iterator it = graphs.cbegin(); it != graphs.cend(); ++it)
  {
    out << "Graph name: " << it->first << '\n';
    basicGraphPrint(out, it->second);
    out << '\n';
  }
  return;
}

void zaitsev::initBase(const char* file, base_t& base)
{
  if (!std::ifstream(file).good())
  {
    throw std::invalid_argument("Initial file does't found");
  }
  std::ifstream in(file);
  using del = zaitsev::Delimiter;
  size_t graphs_nmb = 0;
  in >> Delimiter{ "Graphs" } >> del{"number:" } >> graphs_nmb;
  if (!in)
  {
    throw std::invalid_argument("Intial file read fail");
  }
  for (size_t i = 0; i < graphs_nmb; ++i)
  {
    std::string graph_name;
    in >> del{ "Graph" } >> del{ "name:" } >> graph_name;
    base.insert({ graph_name, basicGraphRead(in) });
  }
  return;
}

void zaitsev::readGraph(base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = args[1];
  const std::string& file = args[2];
  if (graphs.find(graph_name) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\" already exists.");
  }
  std::ifstream input_file(file);
  if (!input_file.good())
  {
    throw std::invalid_argument("File \"" + file + "\" does't found");
  }
  graphs.insert({ graph_name,basicGraphRead(input_file) });
  return;
}

void zaitsev::writeGraph(const base_t& graphs, const std::vector< std::string >& args, std::ostream&)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = args[1];
  const std::string& file = args[2];
  if (std::ifstream(file).good())
  {
    throw std::invalid_argument("File \"" + file + "\" already exists");
  }
  std::ofstream out(file);
  base_t::const_iterator graph = graphs.find(graph_name);
  if (graph == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\" doesn't exist.");
  }
  basicGraphPrint(out, graph->second);
  return;
}

zaitsev::graph_t basicGraphRead(std::istream& in)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    throw std::ios::failure("Input error");
  }
  using namespace zaitsev;
  using del = Delimiter;
  size_t vertices_nmb = 0;
  graph_t new_graph;
  in >> del{ "Vertices" } >> del{ "(" } >> vertices_nmb >> del{ "):" };
  for (size_t i = 0; i < vertices_nmb; ++i)
  {
    std::string vert_name;
    in >> vert_name;
    if (!in)
    {
      throw std::ios_base::failure("Input fail");
    }
    new_graph.insert({ vert_name, unit_t{} });
  }
  size_t edges_nmb = 0;
  in >> del{ "Edges" } >> del{ "(" } >> edges_nmb >> del{ "):" };
  for (size_t i = 0; i < edges_nmb; ++i)
  {
    std::string begin, end;
    int value = 0;
    in >> begin >> del{ "-->" } >> end >> del{ ":" } >> value;
    if (!in)
    {
      throw std::ios_base::failure("Input fail");
    }
    new_graph[begin].insert({ end, value });
  }
  return new_graph;
}

void basicGraphPrint(std::ostream& out, const zaitsev::graph_t& graph, size_t indnent_sz)
{
  using namespace zaitsev;
  std::string indent(indnent_sz, ' ');
  out << "Vertices (" << graph.size() << "):\n";
  size_t counter = 0;

  for (graph_t::const_iterator it = graph.begin(); it != graph.end(); ++it)
  {
    out << indent << it->first << '\n';
    counter += it->second.size();
  }
  out << "Edges (" << counter << "):\n";
  for (graph_t::const_iterator it_gr = graph.begin(); it_gr != graph.end(); ++it_gr)
  {
    for (unit_t::const_iterator it_v = it_gr->second.begin(); it_v != it_gr->second.end(); ++it_v)
    {
      out << indent << it_gr->first << " --> " << it_v->first << " : " << it_v->second << '\n';
    }
  }
  return;
}
