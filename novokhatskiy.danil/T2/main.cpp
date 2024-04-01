#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace novokhatskiy;
  using input_it_t = std::istream_iterator< DataStruct >;
  using output_it_t = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > res;
  while (!std::cin.eof())
  {
    std::copy(input_it_t{std::cin}, input_it_t{}, std::back_inserter(res));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  std::sort(res.begin(), res.end());
  std::copy(res.cbegin(), res.cend(), output_it_t{std::cout, "\n"});
  return 0;
}
