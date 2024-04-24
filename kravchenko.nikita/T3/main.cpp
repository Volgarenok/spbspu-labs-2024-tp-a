#include <fstream>
#include <iostream>
#include "polygonHandler.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Required filename argument\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "File cannot be opened\n";
    return 2;
  }
  using namespace kravchenko;

  try
  {
    PolygonHandler polygonsFromFile;
    polygonsFromFile.inputPolygons(file);
    polygonsFromFile.handleCommands(std::cin, std::cout);
  }
  catch(...)
  {
    file.close();
    return 3;
  }

  file.close();
  return 0;
}
