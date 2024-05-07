#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>

#include "geometry.hpp"
#include "inputShapes.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    return 1;
  }

  std::vector < zhalilov::Polygon > polygons;
  while (!file.eof())
  {
    std::copy(
        std::istream_iterator < zhalilov::Polygon >(file),
        std::istream_iterator < zhalilov::Polygon >(),
        std::back_inserter(polygons)
        );
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
    }
  }
}
