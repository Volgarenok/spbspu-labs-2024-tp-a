#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace ravinskij;
  std::vector< DataStruct > data;
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< DataStruct >{std::cout, "\n"});
  return 0;
}
