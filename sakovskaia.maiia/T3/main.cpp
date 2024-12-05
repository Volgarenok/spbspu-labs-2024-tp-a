#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace sakovskaia;
  std::vector< Polygon > polygons;
  if (argc != 2)
  {
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile.is_open())
  {
    std::cerr << "isn't open\n";
    return 2;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  while (!infile.eof())
  {
    std::copy(input_it_t{infile}, input_it_t{}, std::back_inserter(polygons));
    infile.clear();
    infile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, _1, _2, polygons);
    cmds["MAX"] = std::bind(getMaxMin, _1, _2, polygons);
    cmds["MIN"] = std::bind(getMaxMin, _1, _2, polygons);
    cmds["COUNT"] = std::bind(getCount, _1, _2, polygons);
    cmds["MAXSEQ"] = std::bind(getMaxSeq, _1, _2, polygons);
    cmds["RMECHO"] = std::bind(getRmecho, _1, _2, polygons);
    cmds["RECTS"] = std::bind(getRects, _2, polygons);
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      std::cout << "\n";
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
