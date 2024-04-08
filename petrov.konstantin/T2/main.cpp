#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.h"

int main()
{
  using petrov::DataStruct;
  std::vector< DataStruct > dataStructs;
  while (!std::cin.eof())
  {
    std::istream_iterator< DataStruct > cinItFirst(std::cin);
    std::istream_iterator< DataStruct > cinItLast;
    std::copy(cinItFirst, cinItLast, std::back_inserter(dataStructs));
    if (std::cin.fail())
    {
      std::cin.clear();
      auto nLMax = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(nLMax, '\n');
    }
  }
  std::sort(dataStructs.begin(), dataStructs.end());
  auto dsItBegin = std::begin(dataStructs);
  auto dsItEnd = std::end(dataStructs);
  std::ostream_iterator< DataStruct > coutIt(std::cout, "\n");
  std::copy(dsItBegin, dsItEnd, coutIt);
  return 0;
}
