#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>

#include "shapes.hpp"
int main(int argc, char* argv[])
{
  using namespace artemev;
  if (argc != 2)
  {
    std::cerr << "Error! Incorrect input argc\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error! Files is empty\n";
    return 1;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
  }
}