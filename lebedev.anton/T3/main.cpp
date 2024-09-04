#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::ifstream inputf(argv[1]);
  if (!inputf)
  {
    return 1;
  }
  using namespace lebedev;
  std::vector< Polygon > polygons;
  while (!inputf.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(inputf),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (inputf.fail())
    {
      inputf.clear();
      inputf.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  /////
  std::cout << getArea(*(++polygons.cbegin())) << "\n";
}
