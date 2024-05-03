#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

#include "polygon.hpp"

int main()
{
  using namespace kornienko;
  using input_it_t = std::istream_iterator< Polygon >;
  using output_it_t = std::ostream_iterator< Polygon >;
  std::vector< Polygon > polygons(input_it_t{std::cin}, input_it_t{});
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{std::cin}, input_it_t{}, std::back_inserter(polygons));
  }
  std::copy(polygons.cbegin(), polygons.cend(), output_it_t{std::cout, "\n"});
  return 0;
}
