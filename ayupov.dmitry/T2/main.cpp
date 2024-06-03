#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>

#include "DataStruct.hpp"

int main()
{
  using namespace ayupov;
  using input_it_t = std::istream_iterator< DataStruct >;
  using output_it_t = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > a;
  while (!std::cin.eof())
  {
    std::copy(input_it_t{std::cin}, input_it_t{}, std::back_inserter(a));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  std::sort(a.begin(), a.end());
  std::copy(a.cbegin(), a.cend(), output_it_t{std::cout, "\n"});
  return 0;
}
