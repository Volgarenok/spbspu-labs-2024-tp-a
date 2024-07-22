#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <limits>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace basko;
  if (argc != 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "File not open\n";
    return 1;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  std::vector< Polygon > value;
  while (!in.eof())
  {
    std::copy(input_it_t{ in }, input_it_t{}, std::back_inserter(value));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  in.close();
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(area, std::cref(value), _1, _2);
    commands["COUNT"] = std::bind(count, std::cref(value), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(value), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(value), _1, _2);
    commands["INFRAME"] = std::bind(inframe, std::cref(value), _1, _2);
    commands["ECHO"] = std::bind(echo, std::ref(value), _1, _2);
    commands["RIGHTSHAPES"] = std::bind(rightshapes, std::cref(value), _2);
  }
  std::string cmd = "";
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
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
