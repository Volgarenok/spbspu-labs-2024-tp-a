#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstddef>
#include <limits>
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace ravinskij;
  if (argc < 2)
  {
    std::cerr << "No file is provided\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Couldn't open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  file.close();
  using output_it_t = std::ostream_iterator< Polygon >;
  std::copy(polygons.cbegin(), polygons.cend(), output_it_t{ std::cout, "\n"});
  return 0;
}
