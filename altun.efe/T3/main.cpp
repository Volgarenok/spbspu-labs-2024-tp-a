#include <iostream>
#include <fstream>
#include <vector>
#include "polygon.hpp"

int main(int argc, char **argv)
{
  using namespace altun;
  if (argc < 2)
  {
    std::cerr << "<NOT ENOUGH ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }
   std::vector< Polygon > polygons;
  
}