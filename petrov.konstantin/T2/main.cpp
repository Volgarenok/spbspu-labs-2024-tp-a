#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.h"
#include "IOWork.hpp"

int main()
{
  using petrov::DataStruct;
  std::vector< DataStruct > dataStructs;
  petrov::readFromStream(std::cin, dataStructs);
  std::sort(dataStructs.begin(), dataStructs.end());
  auto dsItBegin = std::begin(dataStructs);
  auto dsItEnd = std::end(dataStructs);
  std::ostream_iterator< DataStruct > coutIt(std::cout, "\n");
  std::copy(dsItBegin, dsItEnd, coutIt);
  return 0;
}
