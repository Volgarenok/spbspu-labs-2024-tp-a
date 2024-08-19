#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include <string>
#include <functional>
#include <streamGuard.hpp>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char **argv)
{
  using namespace altun;
  if (argc < 2)
  {
    std::cerr << "<NOT ENOUGH ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
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

  std::map< std::string, std::function< bool(const Polygon&) > > args;
  {
    using namespace std::placeholders;
    args["EVEN"] = std::bind(std::equal_to< double >{},
        std::bind(std::modulus< size_t >{},
        std::bind(getSize, _1), 2), 0);
    args["ODD"] = std::bind(std::not_equal_to< double >{},
        std::bind(std::modulus< size_t >{},
        std::bind(getSize, _1), 2), 0);
    args["MEAN"] = std::bind(std::equal_to< int >{}, 1, 1);
  }

  std::map<std::string, std::function< bool(const Polygon&) > > argsCount;
  argsCount["EVEN"] = args["EVEN"];
  argsCount["ODD"] = args["ODD"];

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["COUNT"] = std::bind(count,  _1, _2, std::cref(polygons), argsCount);
    cmds["AREA"] = std::bind(getArea, _1, _2, std::cref(polygons), args);
    cmds["MAX"] = std::bind(findMax, _1, _2, std::cref(polygons));
    cmds["MIN"] = std::bind(findMin, _1, _2, std::cref(polygons));
    cmds["MAXSEQ"] = std::bind(maxSeq, _1, _2, std::cref(polygons));
    cmds["ECHO"] = std::bind(echo, _1, _2, std::ref(polygons));
    cmds["SAME"] = std::bind(same, _1, _2, std::cref(polygons));
  }

  std::string cmd = "";
  std::cin >> cmd;
  while (!std::cin.eof())
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
    std::cin >> cmd;
  }
  return 0;
}
