
#include <iostream>
#include <string>
#include "DataStruct.h"


int main()
{
  petrov::DataStruct ds(0, 0, "default");
  std::cin >> ds;
  std::cout << ds.key1_ << ' ' << ds.key2_ << ' ' << ds.key3_ << '\n';
  return 0;
}
