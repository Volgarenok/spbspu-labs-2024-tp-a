#include <iostream>
#include <list>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using namespace spiridonov;
  using input_it_t = std::istream_iterator< DataStruct >;
  std::list< DataStruct > data(input_it_t{ std::cin }, input_it_t{});

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(data));
  }

  using output_it_t = std::ostream_iterator< DataStruct >;
  data.sort();
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });

  return 0;
}
