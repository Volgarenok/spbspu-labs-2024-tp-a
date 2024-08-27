#include <iostream>
#include <functional>
#include <map>
#include <limits>
#include <fstream>
#include <iterator>

#include "polygon.hpp"
#include "cmd.hpp"


int main(int argc, char * argv[])
{
  using namespace ishmuratov;
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!input_file.eof())
  {
    std::copy(input_it_t{input_file}, input_it_t{}, std::back_inserter(polygons));
    input_file.clear();
    input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(get_areas, std::ref(polygons), _1, _2);
    cmds["MAX"] = std::bind(get_max, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(get_min, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(count_polygons, std::cref(polygons), _1, _2);
    cmds["LESSAREA"] = std::bind(get_less_area, std::cref(polygons), _1, _2);
    cmds["MAXSEQ"] = std::bind(get_max_seq, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}