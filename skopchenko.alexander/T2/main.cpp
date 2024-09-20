#include "datastruct.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

int main()
{
  using namespace skopchenko;
  std::vector<DataStruct> dataStructs;

  std::istream_iterator<DataStruct> it(std::cin);
  std::istream_iterator<DataStruct> end;

  std::copy_if(it, end, std::back_inserter(dataStructs),
               [](const DataStruct &data) {
                 return !std::cin.fail();
               });

  std::sort(dataStructs.begin(), dataStructs.end(), compare);

  std::copy(dataStructs.begin(), dataStructs.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}

