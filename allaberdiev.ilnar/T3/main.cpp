#include <fstream>
#include <iostream>
#include <streamGuard.hpp>
#include "polygon.hpp"

int main(int argc, char **argv)
{
  using namespace allaberdiev;
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
}
