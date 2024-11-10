#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include "DataStruct.h"
#include "Commands.h"

int main(int argc, char* argv[])
{
  using namespace stepanov;
  if (argc != 2)
  {
    std::cout << "Incorrect argс\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Incorrect file\n";
    return 1;
  }

  std::vector< Polygon > data;
  Commands commands;

  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string command = inputCommand(std::cin);
      doCommand(data, commands, command, std::cout, std::cin);
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
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
