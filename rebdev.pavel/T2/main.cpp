#include <iostream>
#include <algorithm>
#include <list>
#include <limits>
#include <iterator>

#include "dataStruct.hpp"

int main()
{
  using inputItT = std::istream_iterator< rebdev::dataStruct_t >;
  std::list< rebdev::dataStruct_t > data;
  while (!std::cin.eof())
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  data.sort();

  using outputItT = std::ostream_iterator< rebdev::dataStruct_t >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });

  return 0;
}
