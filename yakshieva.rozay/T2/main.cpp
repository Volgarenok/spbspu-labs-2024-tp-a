#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>
#include "DataStruct.hpp"

int main()
{
  using namespace yakshieva;
  using input_iterator_t = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > dataVect;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_iterator_t{ std::cin }, input_iterator_t{}, std::back_inserter(dataVect));
  }
  std::sort(dataVect.begin(), dataVect.end());
  using output_iterator_t = std::ostream_iterator< DataStruct >;
  std::copy(std::begin(dataVect), std::end(dataVect), output_iterator_t{ std::cout, "\n" });
  return 0;
}
