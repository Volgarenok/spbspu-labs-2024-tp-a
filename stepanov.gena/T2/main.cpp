#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "DataStruct.h"

using namespace stepanov;

int main()
{
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy
    (
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end());
  std::copy
  (
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
