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

  using namespace kuznetsov;

  std::vector< Polygon > polygon;

  if (argc != 2)
  {
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

    std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(polygon));
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, polygon, _1, _2);
    cmds["MAX"] = std::bind(getMax, polygon, _1, _2);
    cmds["MIN"] = std::bind(getMin, polygon, _1, _2);
    cmds["COUNT"] = std::bind(getCount, polygon, _1, _2);
    cmds["SAME"] = std::bind(getSame, polygon, _1, _2);
    cmds["INFRAME"] = std::bind(getInframe, polygon, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}


