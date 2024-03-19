#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.hpp"
#include "DelimiterI.hpp"

int main()
{
  using namespace kuzmina;

  std::vector< DataStruct > data(std::istream_iterator< DataStruct >(std::cin),
                                 std::istream_iterator< DataStruct >{});

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data)
    );

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
