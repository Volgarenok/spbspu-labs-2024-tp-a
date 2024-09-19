#include "dataStruct.hpp"
#include <iterator>
#include <vector>
#include <limits>
#include <algorithm>

int main()
{
  using namespace chernov;

  using input_it_t = std::istream_iterator< chernov::DataStruct >;
  std::vector< chernov::DataStruct > obj;

  while (!(std::cin.eof()))
  {
    if (!(std::cin))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{std::cin}, input_it_t{}, std::back_inserter(obj));
  }

  using output_it_t = std::ostream_iterator< chernov::DataStruct >;

  std::sort(obj.cbegin(), obj.cend());
  std::copy(obj.cbegin(), obj.cend(), output_it_t{std::cout, "\n"});
}
