#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <map>
#include "Shapes.hpp"
#include "Commands.hpp"

using namespace kuzmina;

int main(int argc, char* argv[])
{
  std::vector< Polygon > polygons;

  if (argc < 2)
  {
    std::cerr << "No file given\n";
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

  std::map< std::string, std::function< void(std::istream&, std::ostream&, const std::vector< Polygon >&) > > commands;
  commands["AREA"] = area;
  commands["MAX"] = max;
  commands["MIN"] = min;
  commands["COUNT"] = count;
  commands["RIGHTSHAPES"] = rightshapes;
  commands["SAME"] = same;

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
