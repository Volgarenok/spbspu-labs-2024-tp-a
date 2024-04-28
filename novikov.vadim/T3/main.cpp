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

  cmd::area_args_t area_arguments;

  using namespace std::placeholders;
  area_arguments["EVEN"] = std::bind(cmd::acc_area_if, _1, _2, even_vertexes);
  area_arguments["ODD"] = std::bind(cmd::acc_area_if, _1, _2, odd_vertexes);
  area_arguments["MEAN"] = std::bind(cmd::acc_area_mean, _1, _2, polygons.size());

  cmd::max_args_t max_arguments;

  max_arguments["AREA"] = std::bind(cmd::max_area, _1, _2);
  max_arguments["VERTEXES"] = std::bind(cmd::max_vertexes, _1, _2);

  cmd::min_args_t min_arguments;

  min_arguments["AREA"] = std::bind(cmd::min_area, _1, _2);
  min_arguments["VERTEXES"] = std::bind(cmd::min_vertexes, _1, _2);

  cmd::count_args_t count_arguments;

  count_arguments["EVEN"] = even_vertexes;
  count_arguments["ODD"] = odd_vertexes;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  commands["AREA"] = std::bind(cmd::area, std::cref(area_arguments), std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(cmd::max, std::cref(max_arguments), std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(cmd::min, std::cref(min_arguments), std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(cmd::count, std::cref(count_arguments), std::cref(polygons), _1, _2);

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
