#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include <functional>
#include <limits>
#include "polygon.hpp"
#include "point.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  using command_map_t = std::map< std::string, std::function< void(std::istream &, std::ostream &) > >;
  using input_iter_t = std::istream_iterator< Polygon >;

  if (argc != 2)
  {
    std::cerr << "wrong launch\n";
    return 1;
  }

  collection_t figures;
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "bad file\n";
    return 2;
  }
  while (!input.eof())
  {
    std::copy(input_iter_t{input}, input_iter_t{}, std::back_inserter(figures));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  command_map_t commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(do_area, _1, _2, std::cref(figures));
    commands["MAX"] = std::bind(do_max, _1, _2, std::cref(figures));
    commands["MIN"] = std::bind(do_min, _1, _2, std::cref(figures));
    commands["COUNT"] = std::bind(do_count, _1, _2, std::cref(figures));
    commands["MAXSEQ"] = std::bind(do_maxseq, _1, _2, std::cref(figures));
    commands["INTERSECTIONS"] = std::bind(do_intersections, _1, _2, std::cref(figures));
  }

  std::cout << std::fixed << std::setprecision(1);
  std::string str;
  while (std::cin >> str)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(str)(std::cin, std::cout);
      std::cout << "\n";
    }
    catch (const std::exception &)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
