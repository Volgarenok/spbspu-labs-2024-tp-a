#include <fstream>
#include <iostream>
#include <iterator>
#include <functional>
#include <limits>
#include <map>
#include <exception>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace grechishnikov;

  if (argc < 2)
  {
    std::cerr << "Incorrect launch conditions\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if  (!file.is_open())
  {
    std::cerr << "Cannot access file\n";
    return 2;
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

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    cmds["PERMS"] = std::bind(perms, std::cref(polygons), _1, _2);
    cmds["MAXSEQ"] = std::bind(maxseq, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
