#include <iostream>
#include "data_struct.hpp"

int main()
{
  using namespace erohin;
  DataStruct record;
  std::cin >> record;
  if (!std::cin)
  {
    std::cout << "Wrong input\n";
    return 1;
  }
  std::cout << record << "\n";
  return 0;
}
