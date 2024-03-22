#include <iostream>
#include "format.hpp"

int main()
{
  using namespace erohin;
  double d;
  std::cin >> DoubleFormat{ d };
  if (!std::cin)
  {
    std::cout << "Wrong input\n";
    return 1;
  }
  std::cout << d << "\n";
  return 0;
}
