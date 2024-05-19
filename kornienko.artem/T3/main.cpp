#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>
#include <functional>

#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace kornienko;
  if (argc != 2)
  {
    std::cerr << "wrong file\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile.is_open())
  {
    std::cerr << "isn't open\n";
    return 2;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  std::vector< Polygon > polygons;
  while (!infile.eof())
  {
    std::copy(input_it_t{infile}, input_it_t{}, std::back_inserter(polygons));
    infile.clear();
    infile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  using output_it_t = std::ostream_iterator< Polygon >;
  std::copy(polygons.cbegin(), polygons.cend(), output_it_t{std::cout, "\n"});

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, _1, _2, polygons);
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
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
