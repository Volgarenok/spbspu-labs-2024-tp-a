#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <algorithm>
#include <functional>
#include "commands.hpp"
#include "polygon.hpp"
#include "predicates.hpp"


int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument provided!\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: can't open the file!\n";
    return 2;
  }

  using namespace novikov;
  std::vector< Polygon > polygons;

  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< double(double, const Polygon&) > > area_subcommands;

  using namespace std::placeholders;
  area_subcommands["EVEN"] = std::bind(cmd::acc_area_if, _1, _2, even_vertexes);
  area_subcommands["ODD"] = std::bind(cmd::acc_area_if, _1, _2, odd_vertexes);
  area_subcommands["MEAN"] = std::bind(cmd::acc_area_mean, _1, _2, polygons.size());

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  commands["AREA"] = std::bind(cmd::area, std::cref(area_subcommands), std::cref(polygons), _1, _2);

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << "<ERROR: " << e.what() << ">\n";
    }
  }

  return 0;
}
