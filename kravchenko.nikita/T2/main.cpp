#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace kravchenko;
  using inputItT = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    data.insert(data.cend(), inputItT{ std::cin }, inputItT{});
  }

  std::sort(data.begin(), data.end());

  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
  return 0;
}
