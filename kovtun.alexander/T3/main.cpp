#include <iostream>

#include "polygon.hpp"

int main()
{
  kovtun::Polygon polygon;
  std::cin >> polygon;
  std::cout << polygon.points.size() << "\n";

  return 0;
}
