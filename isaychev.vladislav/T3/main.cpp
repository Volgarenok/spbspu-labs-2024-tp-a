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
  using cmd_t = std::function< void(std::istream &, std::ostream &, const collection_t &) >;
  using command_map_t = std::map< std::string, cmd_t >;
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
  commands["AREA"] = do_area;
  commands["MAX"] = do_max;
  commands["MIN"] = do_min;
  commands["COUNT"] = do_count;
  commands["MAXSEQ"] = do_maxseq;
  commands["INTERSECTIONS"] = do_intersections;

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
      commands.at(str)(std::cin, std::cout, figures);
      std::cout << "\n";
    }
    catch (const std::exception &)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
