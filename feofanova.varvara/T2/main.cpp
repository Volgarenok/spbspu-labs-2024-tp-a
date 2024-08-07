#include "DataStruct.hpp"
#include<vector>
#include <iterator>
#include<limits>
#include<list>

int main()
{
  using feofanova::DataStruct;
  std::list< DataStruct > data;
  while (!std::cin.eof())
  {
    using input_it = std::istream_iterator< DataStruct >;
    std::copy(input_it{ std::cin }, input_it{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  data.sort();
  using output_it = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it{ std::cout, "\n" });
}
