#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>

#include "polygon.hpp"

int main(int argc, char ** argv)
{
  std::ifstream inFile(argv[1]);
  using inputItT = std::istream_iterator< rebdev::Polygon >;
  std::vector< rebdev::Polygon > polygonsVector(inputItT{ inFile }, inputItT{});
  auto it = polygonsVector.begin();
  while (it != polygonsVector.end())
  {
    auto it2 = (*it).points.begin();
    while (it2 != ((*it).points.end()))
    {
      std::cout << "x: " << (*it2).x << "y: " << (*it2).y << '\n';
      ++it2;
    }
    ++it;
  }
  return 0;
}
