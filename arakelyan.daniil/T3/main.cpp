#include <fstream>
#include <iostream>
#include <vector>

#include "polygons.hpp"

int main(int argc, char **argv)
{
  //maxseq rightshapes
  if (argc < 2)
  {
    std::cerr << "<NO SOURCE FILE WITH FIGURES!>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }

  std::vector< int > polygons;
}
