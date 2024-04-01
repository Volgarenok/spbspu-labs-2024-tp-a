#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"


int main()
{
  using namespace grechishnikov;
  std::vector< DataStruct > data{ {10, { 3.1, 3.003 }, "aaa" } };

//  using input_it_t = std::istream_iterator< DataStruct >;
//  std::copy(input_it_t{ std::sin }, input_it_t{}, std::back_inserter(data));

  using output_it_t = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });
}
