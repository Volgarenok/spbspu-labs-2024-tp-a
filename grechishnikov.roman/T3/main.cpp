#include <fstream>
#include <iostream>
#include <iterator>
#include <functional>
#include <limits>
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace grechishnikov;

  if (argc < 2)
  {
    std::cerr << "Incorrect launch conditions\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if  (!file.is_open())
  {
    std::cerr << "Cannot access file\n";
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

  for (size_t i = 0; i < polygons.size(); i++)
  {
    for (size_t j = 0; j < polygons[i].points.size(); j++)
    {
      std::cout << polygons[i].points[j].x << " " << polygons[i].points[j].y << ' ';
    }
    std::cout << '\n';
  }
}
