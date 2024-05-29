#include <iostream>
#include <fstream>
#include <vector>

struct Point
{
  int x, y;
};

struct Polygon
{
  std::vector<Point> points;
};

int main(int argc, char ** argv)
{
  if (argc < 2)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "No such file\n";
    return 1;
  }

  return 0;
}
