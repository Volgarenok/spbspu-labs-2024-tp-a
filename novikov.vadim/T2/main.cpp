#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"
#include "valueI.hpp"
#include "charDelimiterI.hpp"
#include "stringDelimiterI.hpp"

int main()
{
  using namespace novikov;
  std::vector< DataStruct > data;
  std::copy(
    std::istream_iterator< DataStruct >{std::cin},
    std::istream_iterator< DataStruct >{},
    std::back_inserter(data)
  );
  std::copy(
    data.cbegin(),
    data.cend(),
    std::ostream_iterator< DataStruct >{std::cout, "\n"}
  );
}
