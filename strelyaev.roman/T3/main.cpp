#include <fstream>
#include <iostream> //
#include "polygon.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "file error\n";
    return 1;
  }
  strelyaev::Point p1;
  input >> p1;
  std::cout << p1.x << p1.y << "\n";
  return 0;
}