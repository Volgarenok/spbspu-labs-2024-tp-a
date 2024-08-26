#include <iostream>
#include <limits>
#include <string>
#include <complex>
#include <iterator>
#include <list>
#include <algorithm>

#include "DataStruct.hpp"


int main()
{
  using namespace sivkov;
  using data_list = std::list< DataStruct >;
  using input_it_t = std::istream_iterator< DataStruct >;
  using output_it_t = std::ostream_iterator< DataStruct >;

  data_list data(input_it_t{ std::cin }, input_it_t{});

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(data));
  }
  data.sort();
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });
}
