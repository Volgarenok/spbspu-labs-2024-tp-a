#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.hpp"

int main()
{
  using namespace kuzmina;

  using inputIt = std::istream_iterator< DataStruct >;
  using outputIt = std::ostream_iterator< DataStruct >;

  std::vector< DataStruct > data;

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    std::copy(inputIt{ std::cin }, inputIt{}, std::back_inserter(data));
   }

  std::sort(data.begin(), data.end());

  std::copy(std::begin(data), std::end(data), outputIt{ std::cout, "\n" });

  return 0;
}
