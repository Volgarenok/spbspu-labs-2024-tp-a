#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "figures_struct.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;

  std::vector< Polygon > data;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    using input_it_t = std::istream_iterator< Polygon >;
    data.insert(data.begin(), input_it_t{ input }, input_it_t{});
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }
}
