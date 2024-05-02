#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#include "polygon.hpp"

int main(int argc, char ** argv)
{
  std::ifstream inFile(argv[1]);
  std::vector< rebdev::Polygon > polygonsVector;
  using inputItT = std::istream_iterator< rebdev::Polygon >;
  std::copy(inputItT{ inFile }, inputItT{}, std::back_inserter(polygonsVector));
  
  return 0;
}
