#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument\n";
    return 1;
  }

  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cerr << "Error: invalid filename\n";
    return 2;
  }

  using namespace zaparin;

  std::vector< Polygon > polygons;
  using in_it = std::istream_iterator< Polygon >;
  using limits = std::numeric_limits< std::streamsize >;

  while (!fin.eof())
  {
    std::copy(in_it{ fin }, in_it{}, std::back_inserter(polygons));
    if (fin.fail())
    {
      fin.clear();
      fin.ignore(limits::max(), '\n');
    }
  }
  fin.close();

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(cmdArea, std::ref(polygons), _1, _2);

  cmds["MAX"] = std::bind(cmdMax, std::ref(polygons), _1, _2);

  cmds["MIN"] = std::bind(cmdMin, std::ref(polygons), _1, _2);

  cmds["COUNT"] = std::bind(cmdCount, std::ref(polygons), _1, _2);

  cmds["MAXSEQ"] = std::bind(cmdMaxSeq, std::ref(polygons), _1, _2);

  cmds["INTERSECTIONS"] = std::bind(cmdIntersections, std::ref(polygons), _1, _2);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(limits::max(), '\n');
  }
}

