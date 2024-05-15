#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstddef>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace ravinskij;
  if (argc < 2)
  {
    std::cerr << "No file is provided\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Couldn't open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();


  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(ravinskij::area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(ravinskij::max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(ravinskij::min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(ravinskij::count, std::cref(polygons), _1, _2);
    commands["INTERSECTIONS"] = std::bind(ravinskij::intersections, std::cref(polygons), _1, _2);
    commands["INFRAME"] = std::bind(ravinskij::inframe, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
      std::cout << '\n';
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
