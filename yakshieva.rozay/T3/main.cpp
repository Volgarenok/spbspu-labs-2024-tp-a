#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include "Commands.hpp"
#include "Polygon.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID_ARGUMENT>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "File couldn't be opened " << argv[1] << std::endl;
    return 1;
  }
  std::vector< yakshieva::Polygon > polygons;
  using input_it_t = std::istream_iterator< yakshieva::Polygon >;
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
    cmds["AREA"] = std::bind(yakshieva::doAreaCommand, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(yakshieva::doMaxCommand, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(yakshieva::doMinCommand, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(yakshieva::doCountCommand, std::cref(polygons), _1, _2);
    cmds["LESSAREA"] = std::bind(yakshieva::doLessAreaCommand, std::cref(polygons), _1, _2);
    cmds["RMECHO"] = std::bind(yakshieva::doRmechoCommand, std::ref(polygons), _1, _2);
    cmds["ECHO"] = std::bind(yakshieva::doEchoCommand, std::ref(polygons), _1, _2);
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
