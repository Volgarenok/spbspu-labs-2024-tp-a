#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <deque>

#include "polygon.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error argument\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Invalid file\n";
    return 1;
  }
  std::vector< chernikova::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    using iter = std::istream_iterator< chernikova::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }
}
