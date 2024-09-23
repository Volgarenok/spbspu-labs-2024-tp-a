#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>

#include "Geometry.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error argument\n";
    return EXIT_FAILURE;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Invalid file\n";
    return EXIT_FAILURE;
  }
  std::vector< serter::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< serter::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  using namespace std::placeholders;
  commands.insert(std::make_pair("AREA", std::bind(serter::area, std::cref(data), _1, _2)));
  commands.insert(std::make_pair("MIN", std::bind(serter::min, std::cref(data), _1, _2)));
  commands.insert(std::make_pair("MAX", std::bind(serter::max, std::cref(data), _1, _2)));
  commands.insert(std::make_pair("COUNT", std::bind(serter::count, std::cref(data), _1, _2)));
  commands.insert(std::make_pair("ECHO", std::bind(serter::echo, std::ref(data), _1, _2)));
  commands.insert(std::make_pair("RMECHO", std::bind(serter::rmEcho, std::ref(data), _1, _2)));
  commands.insert(std::make_pair("LESSAREA", std::bind(serter::lessArea, std::cref(data), _1, _2)));
  std::string command;
  while (std::cin >> command)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}

