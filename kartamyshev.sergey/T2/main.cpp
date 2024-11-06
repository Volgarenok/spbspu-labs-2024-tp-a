#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include "DataStruct.h"
int main()
{
  using namespace kartamyshev;
  using input_it = std::istream_iterator< DataStruct >;

  std::list< DataStruct > data(input_it{ std::cin }, input_it{});
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it{ std::cin }, input_it{}, std::back_inserter(data));
  }

  data.sort();
  using output_it = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it{ std::cout, "\n" });
  return 0;
}
