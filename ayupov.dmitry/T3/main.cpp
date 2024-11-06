#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace ayupov;
  if (argc != 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "Can't open file\n";
    return 2;
  }
  std::vector< Polygon > polygon;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!input.eof())
  {
    std::copy(input_it_t{input}, input_it_t{}, std::back_inserter(polygon));
    input.clear();
    input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(area, std::cref(polygon), _1, _2);
  cmds["MAX"] = std::bind(max, std::cref(polygon), _1, _2);
  cmds["MIN"] = std::bind(min, std::cref(polygon), _1, _2);
  cmds["COUNT"] = std::bind(count, std::cref(polygon), _1, _2);
  cmds["ECHO"] = std::bind(echo, std::ref(polygon), _1, _2);
  cmds["INFRAME"] = std::bind(inFrame, std::cref(polygon), _1, _2);
  cmds["MAXSEQ"] = std::bind(maxSeq, std::cref(polygon), _1, _2);
  cmds["LESSAREA"] = std::bind(lessArea, std::cref(polygon), _1, _2);
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
}
