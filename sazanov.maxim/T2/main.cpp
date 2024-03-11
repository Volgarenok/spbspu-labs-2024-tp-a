#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

int main()
{
  std::vector< sazanov::DataStruct > data;

  using input_it_t = std::istream_iterator< sazanov::DataStruct >;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::copy(
      input_it_t{std::cin},
      input_it_t{},
      std::back_inserter(data)
    );
  }

  std::sort(data.begin(), data.end());

  using output_it_t = std::ostream_iterator< sazanov::DataStruct >;
  std::copy(
    data.cbegin(),
    data.cend(),
    output_it_t{std::cout, "\n"}
  );
}
