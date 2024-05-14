#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include "dataStruct.hpp"

int main()
{
  std::vector< demidenko::DataStruct > vec;

  using InputIt = std::istream_iterator< demidenko::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(InputIt{ std::cin }, InputIt{}, std::back_inserter(vec));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(vec.begin(), vec.end());

  using OutputIt = std::ostream_iterator< demidenko::DataStruct >;
  std::copy(vec.cbegin(), vec.cend(), OutputIt{ std::cout, "\n" });
  return 0;
}
