#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

#include "datastruct.h"

int main()
{
  using namespace skopchenko;
  std::vector<DataStruct> dataStructs;

  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(dataStructs));

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(dataStructs.begin(), dataStructs.end(), compare);

  std::copy(dataStructs.cbegin(), dataStructs.cend(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
