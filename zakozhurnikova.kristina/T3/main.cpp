#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  if (argc < 2)
  {
    std::cerr << "Incorrect number of arguments\n";
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
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();
}
