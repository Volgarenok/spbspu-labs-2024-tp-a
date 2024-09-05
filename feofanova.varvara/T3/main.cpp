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
  cmds["LESSAREA"] = std::bind(feofanova::Lessarea, std::ref(polygons), _1, _2);
  cmds["PERMS"] = std::bind(feofanova::Perms, std::ref(polygons), _1, _2);
  cmds["COUNT"] = std::bind(feofanova::Count, std::cref(polygons), _1, _2);

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
