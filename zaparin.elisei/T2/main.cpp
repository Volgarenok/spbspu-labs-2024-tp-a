#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <algorithm>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using namespace zaparin;

  std::list< DataStruct > data;

  using is_iterator = std::istream_iterator< DataStruct >;
  using os_iterator = std::ostream_iterator< DataStruct >;

  while (!std::cin.eof())
  {
    std::copy(
      is_iterator(std::cin),
      is_iterator(),
      std::back_inserter(data));

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  data.sort();

  std::copy(data.begin(), data.end(), os_iterator(std::cout, "\n"));
}

