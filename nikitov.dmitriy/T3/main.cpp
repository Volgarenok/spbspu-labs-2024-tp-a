#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include "figures_struct.hpp"
#include "command_type.hpp"

bool isPolygonCorrect(const nikitov::Polygon& value)
{
  return value.points.size() != 0;
}

int main(int argc, char* argv[])
{
  using namespace nikitov;

  std::vector< Polygon > data;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    using input_it_t = std::istream_iterator< Polygon >;
    std::copy_if(input_it_t{ input }, input_it_t{}, std::back_inserter(data), isPolygonCorrect);
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  using input_it_t = std::istream_iterator< CommandType >;
  std::vector< CommandType > commandsLog;
  std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(commandsLog));
}
