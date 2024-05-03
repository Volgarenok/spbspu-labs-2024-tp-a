#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

#include "polygon.hpp"

int main()
{
  using namespace kornienko;
  using input_it_t = std::istream_iterator< Point >;
  using output_it_t = std::ostream_iterator< Point >;
  int n = 0;
  while (!std::cin.eof())
  {
    Polygon polygon;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> n;
    std::copy_n(input_it_t{std::cin}, n, std::back_inserter(polygon.points));
    std::cout << n << " ";
    std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{std::cout, " "});
    std::cout << "\n";
  }
  return 0;
}
