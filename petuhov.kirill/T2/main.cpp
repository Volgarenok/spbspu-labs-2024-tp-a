#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datastruct.hpp"

int main()
{
  std::vector<petuhov::DataStruct> dataList;

  std::copy(std::istream_iterator<petuhov::DataStruct>(std::cin),
            std::istream_iterator<petuhov::DataStruct>(),
            std::back_inserter(dataList));

  std::sort(dataList.begin(), dataList.end());

  std::copy(dataList.begin(), dataList.end(),
            std::ostream_iterator<petuhov::DataStruct>(std::cout, "\n"));

  return 0;
}
