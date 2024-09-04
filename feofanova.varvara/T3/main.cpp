#include "StreamGuard.hpp"
#include "polygon.hpp"
#include "cmds.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

namespace feofanova
{
  void lessarea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
  {
    Polygon polygon;
    in >> polygon;
    if (polygon.points.empty() || in.peek() != '\n')
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    out << std::count_if(data.cbegin(), data.cend(), std::bind(isAreaLess, _1, polygon)) << '\n';
  };

  void perms(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
  {
    Polygon polygon;
    in >> polygon;
    if (polygon.points.empty() || in.peek() != '\n')
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    out << std::count_if(data.cbegin(), data.cend(), std::bind(Perms, _1, polygon)) << '\n';
  };
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

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["LESSAREA"] = std::bind(lessarea, std::ref(polygons), _1, _2);
  cmds["PERMS"] = std::bind(perms, std::ref(polygons), _1, _2);

  std::string command = "";
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
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
