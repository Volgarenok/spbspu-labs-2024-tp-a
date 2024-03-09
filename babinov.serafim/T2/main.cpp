#include <iostream>

#include "dataStruct.hpp"

int main()
{
  using namespace babinov;

  DataStruct dataStruct{81, 100, "text"};
  std::cout << dataStruct;
}
