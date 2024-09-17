#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include "data_struct.hpp"

int main()
{
  using namespace lebedev;
  std::vector< DataStruct > data;
  using input_iter = std::istream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_iter{ std::cin }, input_iter{}, std::back_inserter(data));
  }
  std::sort(data.begin(), data.end());
  using output_iter = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_iter(std::cout, "\n"));
  return 0;
}
