#include "i_o_processing.hpp"
#include <fstream>
#include <iomanip>
#include <delimiter.hpp>
#include <stream_guard.hpp>

zaitsev::graph_t basic_graph_read(std::istream& in);
void basic_graph_print(std::ostream& out, const zaitsev::graph_t& graph, size_t indnent_sz = 2);

std::ostream& zaitsev::listGraphs(const base_t& graphs, std::istream&, std::ostream& out)
{
  if (graphs.empty())
  {
    return out << "No saved graphs\n";
  }
  zaitsev::StreamGuard guard(out);
  auto c_it = graphs.cbegin();
  for (size_t i = 1; i < graphs.size() + 1; ++i)
  {
    out << std::setw(3) << i << ". " << c_it->first << '\n';
    ++c_it;
  }
  return out;
}

void zaitsev::print_help()
{
  using namespace std;
  string indent(2, ' ');
  cout << "Help:\n";
  cout << "1. read <file> <graph-name>\n" << indent;
  cout << "Read the graph from the file <file>, and assign it the name <graph-name>.\n\n";
  cout << "2. write <graph> <file>\n" << indent;
  cout << "Write a graph <graph> to a file <file>.\n\n";
  cout << "3. list_of_graphs\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n";
  cout << "4. print <graph-name>\n" << indent;
  cout << "Print a description of the graph <graph-name>.\n\n";
  cout << "5. create_graph <graph-name>\n" << indent;
  cout << "Create an empty graph named <graph-name>.\n\n";
  cout << "6. delete_graph <graph>\n" << indent;
  cout << "Delete a graph named <graph-name>.\n\n";
  cout << "7. add_vertex <graph> <vertex> \n" << indent;
  cout << "Add a vertex <vertex> to the graph <graph-name>.\n\n";
  cout << "8. add_edge [-check] <graph> <begin> <end> <value>\n" << indent;
  cout << "Add an edge to the graph <graph> that connects the vertices <begin> <end> with the value <value>.\n\n";
  cout << "9. merge [-check] <new-graph> <graph-1> <graph-2> \n" << indent;
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

std::ostream& zaitsev::printGraph(const base_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  in >> graph_name;
  base_t::const_iterator graph = graphs.find(graph_name);
  if (graph == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
  }
  out << "Graph name: " << graph->first << '\n';
  basic_graph_print(out, graph->second);
  return out;
}

void zaitsev::dump(const base_t& graphs, std::istream& in, std::ostream&)
{
  std::string file;
  in >> file;
  if (std::ifstream(file).good())
  {
    throw std::invalid_argument("File already exists");
  }

  std::ofstream out(file);
  out << "Graphs number: " << graphs.size() << '\n';
  for (base_t::const_iterator it = graphs.cbegin(); it != graphs.cend(); ++it)
  {
    out << "Graph name: " << it->first << '\n';
    basic_graph_print(out, it->second);
    out << '\n';
  }
  return;
}

void zaitsev::init_base(const char* file, base_t& base)
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
    base.insert({ graph_name, basic_graph_read(in) });
  }
  return;
}

void zaitsev::readGraph(base_t& graphs, std::istream& in, std::ostream&)
{
  std::string graph_name, file;
  in >> graph_name >> file;
  std::ifstream input_file(file);
  if (!input_file.good())
  {
    throw std::invalid_argument("File \"" + file + "\" does't found");
  }
  graphs.insert({ graph_name,basic_graph_read(input_file) });
  return;
}

void zaitsev::writeGraph(const base_t& graphs, std::istream& in, std::ostream&)
{
  std::string graph_name;
  std::string file;
  in >> graph_name >> file;
  if (std::ifstream(file).good())
  {
    throw std::invalid_argument("File \"" + file + "\" already exists");
  }
  std::ofstream out(file);
  base_t::const_iterator graph = graphs.find(graph_name);
  if (graph == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\" doesn't exists.");
  }
  basic_graph_print(out, graph->second);
  return;
}

zaitsev::graph_t basic_graph_read(std::istream& in)
{
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

void basic_graph_print(std::ostream& out, const zaitsev::graph_t& graph, size_t indnent_sz)
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
