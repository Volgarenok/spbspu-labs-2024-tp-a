#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>

#include "Geometry.h"
#include "Commands.h"

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
  commands.insert(std::make_pair("ECHO", std::bind(serter::echo, std::ref(data), _1, _2)));
  commands.insert(std::make_pair("RMECHO", std::bind(serter::rmEcho, std::ref(data), _1, _2)));
  commands.insert(std::make_pair("LESSAREA", std::bind(serter::lessArea, std::cref(data), _1, _2)));
  while (!std::cin.eof())
  {
    try
    {
      std::string command;
      std::cin >> command;
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      std::cin.setstate(std::ios::failbit);
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
    if (!std::cin)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cout << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

