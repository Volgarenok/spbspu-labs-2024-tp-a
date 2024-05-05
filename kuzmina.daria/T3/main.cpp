#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <vector>
#include <map>
#include <limits>
#include "Shapes.hpp"
#include "Commands.hpp"

using namespace kuzmina;

int main(int argc, char* argv[])
{
  std::vector< Polygon > polygons;

  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  using input_it_t = std::istream_iterator< Polygon >;

  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(polygons));
  }

  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&, const std::vector< Polygon >&) > > commands;
  commands["AREA"] = std::bind(area, _1, _2, polygons);
  commands["MAX"] = std::bind(max, _1, _2, polygons);
  commands["MIN"] = std::bind(min, _1, _2, polygons);
  commands["COUNT"] = std::bind(count, _1, _2, polygons);
  commands["RIGHTSHAPES"] = std::bind(rightshapes, _2, polygons);
  commands["SAME"] = std::bind(same, _1, _2, polygons);

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, polygons);
      std::cout << '\n';
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
