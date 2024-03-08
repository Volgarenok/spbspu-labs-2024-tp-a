#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  using namespace kravchenko::dataStruct;
  using inputItT = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data(inputItT{ std::cin }, inputItT{});
  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
  return 0;
}