#include <fstream>
#include <iostream>
#include <iterator>
#include "shapes.hpp"

int main(int argc, char* argv[])
{
  using namespace babinov;
  using input_it_t = std::istream_iterator< Polygon >;

  char* fileName = argv[1];
  std::ifstream file(fileName);
  std::vector< Polygon > shapes{input_it_t(file), input_it_t()};
}
