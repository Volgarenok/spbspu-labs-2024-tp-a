#include <iostream>
#include "datastruct.hpp"

int main()
{
  kuznetsov::Polygon point;
  std::cin >> point;
  if (std::cin)
  {
    std::cout << "True\n";
  }
  else
  {
    std::cout << "False\n";
  }
}
