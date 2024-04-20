#include <iostream>
#include <fstream>
#include <iterator>
#include "polygon.hpp"

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument provided!\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: can't open the file!\n";
    return 2;
  }

  using namespace novikov;
  std::vector< Polygon > polygons;

  using input_it_t = std::istream_iterator< Polygon >;
  std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));

  return 0;
}
