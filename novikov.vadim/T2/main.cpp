#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace novikov;
  std::vector< DataStruct > data;
  std::copy(
    std::istream_iterator< DataStruct >{std::cin},
    std::istream_iterator< DataStruct >{},
    std::back_inserter(data)
  );
  std::sort(data.begin(), data.end());
  std::copy(
    data.cbegin(),
    data.cend(),
    std::ostream_iterator< DataStruct >{std::cout, "\n"}
  );
}
