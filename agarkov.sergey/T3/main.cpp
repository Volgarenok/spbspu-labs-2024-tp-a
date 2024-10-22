#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include "polygon.hpp"
#include "commands.hpp"
#include "commandsdict.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Error file\n";
    return 1;
  }

  std::vector< agarkov::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< agarkov::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }

  agarkov::Commands dict_wiht_cmd;

  while (!std::cin.eof())
  {
    try
    {
      std::string command = agarkov::inputCommand(std::cin);
      agarkov::doCommand(data, dict_wiht_cmd, command, std::cout, std::cin);
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
      std::cout << "<INVALID COMMAND>";
      std::cout << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
