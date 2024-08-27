#include "StreamGuard.hpp"
#include "polygon.hpp"
#include "cmds.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <istream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>

namespace feofanova
{
  void lessarea(const std::vector< Polygon >& input, const std::vector< Polygon >& data, std::istream&, std::ostream& out)
  {
    out << std::count_if(input, data, isAreaLess);
  }
  void perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data, std::istream&, std::ostream& out)
  {
    out << std::count_if(input, data, perms);
  }
}

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

  using namespace feofanova;

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

  std::map< std::string, std::function< void(size_t numOfVetexes, std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["LESSAREA"] = std::bind(lessarea, polygons, _1, _2, _3);
  cmds["PERMS"] = std::bind(perms, polygons, _1, _2, _3);

  size_t nov;
  std::string command, parameter;
  while (std::cin >> command)
  {
    parameter = "";
    if (std::cin.peek() != '\n')
    {
      std::cin >> parameter;
    }
    cmds.at(command + parameter)(nov, std::cin, std::cout);
    std::cin.clear();
    std::cin.ignore(limits::max(), '\n');
  }
}
