#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "polygon.hpp"

int main(int argc, char * argv[]) {
  using namespace baranov;
  if (argc < 2)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }

  std::vector< Polygon > shapes;
  using in_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(in_it_t{ file }, in_it_t{}, std::back_inserter(shapes));
  }
}

