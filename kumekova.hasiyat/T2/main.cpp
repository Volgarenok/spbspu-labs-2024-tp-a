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

  InputIter iter(std::cin);
  InputIter end;

  while (iter != end)
  {
    DataStruct dataStruct;
    try {
      *iter >> dataStruct;
      data.push_back(dataStruct);
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    ++iter;
  }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), OutputIter(std::cout, "\n"));

  return 0;
}
