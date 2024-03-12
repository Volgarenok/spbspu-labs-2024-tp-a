#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct DataStruct
{
  private:
    double key1_;
}

int main()
{
  using input_it_t = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data(input_it_t{std::cin}, input_it_t{});

  using output_it_t = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it_t{std::cout, "\n"});
}
