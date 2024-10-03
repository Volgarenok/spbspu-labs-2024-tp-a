#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

#include "DataStruct.hpp"

int main()
{
  using namespace kumekova;
  std::vector<DataStruct> data;

  while (!std::cin.eof()) {
    DataStruct record;
    if (std::cin >> record) {
      data.push_back(record);
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
