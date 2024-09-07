#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <limits>
#include "figures.hpp"

using namespace timchishina;
int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<INVALID FILE>\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  using inIterator = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(inIterator{file}, inIterator{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();
  return 0;
}
