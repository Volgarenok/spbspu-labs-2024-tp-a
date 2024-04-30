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

  Polygon polygon;
  using input_it_t = std::istream_iterator< Point >;
  std::size_t vertexCount = 0;
  while (!file.eof())
  {
    file >> vertexCount;
    std::copy_n(input_it_t{ file }, vertexCount, std::back_inserter(polygon.points));
    if (file)
    {
      std::copy(polygon.points.cbegin(), polygon.points.cend(),
      std::ostream_iterator< Point >(std::cout, " "));
      std::cout << '\n';
    }
    polygon.points.clear();
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  file.close();
  return 0;
}
