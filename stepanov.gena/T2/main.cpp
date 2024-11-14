#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "DataStruct.h"

int main()
{
  std::vector< stepanov::DataStruct > data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy
    (
      std::istream_iterator< stepanov::DataStruct >(std::cin),
      std::istream_iterator< stepanov::DataStruct >(),
      std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end());
  std::copy
  (
    std::begin(data),
    std::end(data),
    std::ostream_iterator< stepanov::DataStruct >(std::cout, "\n")
  );

  return 0;
}
