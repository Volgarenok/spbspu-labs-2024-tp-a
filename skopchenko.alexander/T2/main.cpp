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
  std::string inputLine;

  while (std::getline(std::cin, inputLine)) {
    std::istringstream iss(inputLine);
    DataStruct data;
    if (iss >> data) {
      dataStructs.push_back(data);
    }
    else {
      std::cin.clear();
    }
  }

  std::sort(dataStructs.begin(), dataStructs.end(), compare);

  std::copy(dataStructs.begin(), dataStructs.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}


