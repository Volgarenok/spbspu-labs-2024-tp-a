#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include "dataStruct.hpp"

int main()
{
  using namespace allaberdiev;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    using input_it = std::istream_iterator< DataStruct >;
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  using output_it = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});
}
