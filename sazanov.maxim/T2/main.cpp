#include "DataStruct.hpp"
#include <iostream>

int main()
{
  sazanov::DataStruct exp{0, 0, ""};
  std::cin >> exp;
  std::cout << exp.key1 << ' ' << exp.key2 << ' ' << exp.key3;
}
