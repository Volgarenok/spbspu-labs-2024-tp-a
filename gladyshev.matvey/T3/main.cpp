#include <iostream>
#include <fstream>
#include <limits>
#include <iterator>

#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
  }
  else
  {
    std::cerr << "Bad file input\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  while (!file.eof())
  {
    if (!file)
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< Polygon >{file},
      std::istream_iterator< Polygon >{},
      std::back_inserter(polygons)
    );
  }
  for (const auto& area: polygons)
  {
    std::cout << findArea(area) << "\n";
  }
}
