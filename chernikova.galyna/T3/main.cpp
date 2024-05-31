#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <exception>

#include "polygon.hpp"
#include "commands.hpp"
#include <interface.hpp>

int main(int argc, char* argv[])
{
  using namespace chernikova;

  if (argc != 2)
  {
    std::cout << "Error argument\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Invalid file\n";
    return 1;
  }

  std::vector< Polygon > data;

  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
    }
    using iter = std::istream_iterator< Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }

  while (!std::cin.eof())
  {
    try
    {
      doCommand(data, std::cout, std::cin);
    }
    catch (const std::invalid_argument& error)
    {
      break;
    }
  }

  return 0;
}
