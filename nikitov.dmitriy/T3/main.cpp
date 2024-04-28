#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "figures_struct.hpp"

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

  std::string command;
  while (std::cin >> command)
  {

  }
}
