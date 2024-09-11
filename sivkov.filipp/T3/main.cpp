#include <iostream>
#include <map>
#include <fstream>
#include <functional>
#include <algorithm>
#include <string>
#include <iterator>
#include "commands.hpp"
#include "polygon.hpp"


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "error cmd\n";
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "error file\n";
    return 1;
  }

  using namespace sivkov;
  std::vector< Polygon > polygons;
  using input_iter = std::istream_iterator< Polygon >;
  while (!in.eof())
  {
    std::copy(input_iter{ in }, input_iter{}, std::back_inserter(polygons));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  using treeOfCmd = std::map < std::string, std::function < void(std::istream&, std::ostream&) > >;
  using namespace std::placeholders;
  treeOfCmd cmd;

  cmd["MIN"] = std::bind(min, _1, _2, polygons);
  cmd["MAX"] = std::bind(max, _1, _2, polygons);
  cmd["AREA"] = std::bind(area, _1, _2, polygons);
  cmd["COUNT"] = std::bind(count, _1, _2, polygons);
  cmd["PERMS"] = std::bind(perms, _1, _2, polygons);
  cmd["INFRAME"] = std::bind(inFrame, _1, _2, polygons);

  std::string arg = "";
  while (std::cin >> arg)
  {
    try
    {
      cmd.at(arg)(std::cin, std::cout);
      std::cout << "\n";
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
  }
}
