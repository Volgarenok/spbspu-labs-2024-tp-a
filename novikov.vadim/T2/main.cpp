#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using namespace novikov;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    using input_it_t = std::istream_iterator< DataStruct >;
    std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  using output_it_t = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });
}
