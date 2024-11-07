#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

using namespace skopchenko;
int main()
{
  using namespace skopchenko;

  std::vector< DataStruct > data;
  using input_it = std::istream_iterator< DataStruct >;
  using output_it = std::ostream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});
}

