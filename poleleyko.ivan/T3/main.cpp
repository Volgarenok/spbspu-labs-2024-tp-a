#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <limits>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char * argv[]) {
  using namespace poleleyko;
  if (argc < 2)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }

  std::vector< Polygon > shapes;
  using in_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(in_it_t{ file }, in_it_t{}, std::back_inserter(shapes));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, std::cref(shapes), _1, _2);
    cmds["MAX"] = std::bind(max, std::cref(shapes), _1, _2);
    cmds["MIN"] = std::bind(min, std::cref(shapes), _1, _2);
    cmds["COUNT"] = std::bind(count, std::cref(shapes), _1, _2);
    cmds["RECTS"] = std::bind(rect, std::cref(shapes), _1, _2);
    cmds["INFRAME"] = std::bind(inFrame, std::cref(shapes), _1, _2);
    cmds["LESSAREA"] = std::bind(lessArea, std::cref(shapes), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}