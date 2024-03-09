#include <iostream>
#include <bitset>
#include <string>

#include "dataStruct.hpp"

int main()
{
  using namespace babinov;

  std::cout << "DataStruct operators test:" << '\n';
  DataStruct struct1{81, 25, "test"};
  DataStruct struct2{81, 25, "test"};
  std::cout << (struct1 == struct2) << '\n';
  struct1.key2 = 37;
  std::cout << (struct1 < struct2) << '\n';
  struct2.key1 = 100;
  std::cout << (struct1 <= struct2) << '\n';
  struct2.key3 = "testtest";
  std::cout << (struct1 != struct2) << '\n';
}
