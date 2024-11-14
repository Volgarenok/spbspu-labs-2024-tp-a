#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <limits>
#include "datastruct.hpp"
#include "key_input.hpp"

int main()
{
  using namespace prisyach;
  using input_iterator = std::istream_iterator< DataStruct >;
  using output_iterator = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(input_iterator(std::cin), input_iterator(), std::inserter(data, data.end()));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(data.begin(), data.end(), output_iterator(std::cout, "\n"));
  return 0;
}
