#include <iostream>

#include "dataStruct.hpp"

int main()
{
  using namespace babinov;

  DataStruct dataStruct{};
  std::cin >> dataStruct;
  std::cout << dataStruct << '\n';
}
