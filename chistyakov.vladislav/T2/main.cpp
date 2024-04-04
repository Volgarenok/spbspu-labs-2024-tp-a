#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
  using input_it_t = std::istream_iterator< int >;
  std::vector< int > data(input_it_t{std::cin}, input_it_t{});

  using output_it_t = std::ostream_iterator< int >;
  std::copy(data.cbegin(), data.cend(), output_it_t{std::cout, "\n"});
}
