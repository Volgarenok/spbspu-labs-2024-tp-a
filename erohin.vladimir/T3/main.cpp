#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include "polygon.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  std::vector< Polygon > context;
  //while (!file.eof()) { std::string token; file >> token; std::cout << " " << token; }
  while (!file.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(file),
      std::istream_iterator< Polygon >(),
      std::back_inserter(context)
    );
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::copy(
    context.cbegin(),
    context.cend(),
    std::ostream_iterator< Polygon >(std::cout, "\n")
  );

  using func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, func > command;
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  return 0;
}
