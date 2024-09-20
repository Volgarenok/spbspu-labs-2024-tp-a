#include "datastruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
  std::vector <skopchenko::DataStruct> dataStructs;
  std::copy(std::istream_iterator<skopchenko::DataStruct>(std::cin),
            std::istream_iterator<skopchenko::DataStruct>(),
            std::back_inserter(dataStructs));
  std::sort(dataStructs.begin(), dataStructs.end(), skopchenko::compare);
  std::copy(dataStructs.begin(), dataStructs.end(),
            std::ostream_iterator<skopchenko::DataStruct>(std::cout, "\n"));

  return 0;
}
