#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "data_struct.hpp"

int main()
{
  using sakovskaia::DataStruct;
  std::vector< DataStruct > data_struct;
  using input_it = std::istream_iterator< DataStruct >;
  using output_it = std::ostream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data_struct));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data_struct.begin(), data_struct.end());
  std::copy(data_struct.cbegin(), data_struct.cend(), output_it{std::cout, "\n"});
}
