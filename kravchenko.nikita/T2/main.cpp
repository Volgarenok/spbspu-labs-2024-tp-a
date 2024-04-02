#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace kravchenko;
  using inputItT = std::istream_iterator< DataStruct >;
  std::deque< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::sort(data.begin(), data.end());

  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
  return 0;
}
