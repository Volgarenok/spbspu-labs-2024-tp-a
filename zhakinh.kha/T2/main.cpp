#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "delimiter.hpp"
#include "dataStruct.hpp"

int main()
{
  using zhakha::DataStruct;
  using input_it = std::istream_iterator< DataStruct >;
  using output_it = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(input_it{ std::cin }, input_it{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(),'\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), output_it{ std::cout, "\n" });

  return 0;
}
