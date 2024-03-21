#include <iostream>
#include "delimeter.hpp"

int main()
{
  using namespace erohin;
  double d = 0;
  std::cin >> d >> Delimeter{ 'd' };
  if (!std::cin)
  {
    std::cout << "Wrong input\n";
    return 1;
  }
  std::cout << d << "\n";
  return 0;
}
