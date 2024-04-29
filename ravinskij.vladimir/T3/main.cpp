#include <iostream>
#include <iterator>
#include <algorithm>
#include "polygon.hpp"
int main()
{
  using namespace ravinskij;
  int n;
  using input_it_t = std::istream_iterator< Point >;
  using output_it_t = std::ostream_iterator< Point >;
  while (!std::cin.eof())
  {
    std::cin >> n;
    Polygon polygon;
    std::copy_n(input_it_t{std::cin}, n, std::back_inserter(polygon.points));
    std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{std::cout, " "});
    std::cout << '\n';
  }
  return 0;
}
