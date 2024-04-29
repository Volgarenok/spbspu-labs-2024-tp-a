#include <iostream>
#include <iterator>
#include <algorithm>
#include "polygon.hpp"
int main()
{
  using namespace ravinskij;
  int n = 0;
  using input_it_t = std::istream_iterator< Point >;
  using output_it_t = std::ostream_iterator< Point >;
  std::cin >> n;
  Polygon polygon;
  std::copy_n(input_it_t{std::cin}, n, std::back_inserter(polygon.points));
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{std::cout, " "});
  std::cout << '\n';
  return 0;
}
