#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <deque>
#include <exception>

#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
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
  std::vector< chernikova::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    using iter = std::istream_iterator< chernikova::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }
  chernikova::Commands dict_with_cmd;
  while (!std::cin.eof())
  {
    try
    {
      std::string command = chernikova::inputCommand(std::cin);
      dict_with_cmd.doCommand(data, dict_with_cmd, command, std::cout, std::cin);
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what();
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
    if (!std::cin)
    {
      std::cout << "<INVALID COMMAND>";
      std::cout << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
