#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

#include "DataStruct.hpp"

int main()
{
  using namespace kumekova;
  using InputIter = std::istream_iterator<DataStruct>;
  using OutputIter = std::ostream_iterator<DataStruct>;

  constexpr auto MaxStreamSize = std::numeric_limits<std::streamsize>::max();

  std::vector<DataStruct> data;

  while (!std::cin.eof()) {
    DataStruct record;
        if (std::cin >> record) {
            data.push_back(record);
        } else {
            std::cin.clear();
            std::cin.ignore(MaxStreamSize, '\n');
        }
    }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), OutputIter(std::cout, "\n"));

  return 0;
}
