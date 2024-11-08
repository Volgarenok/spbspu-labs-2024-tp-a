#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"
#include <limits>

int main()
{
  std::list< kumekova::DataStruct > data{};
  while (!std::cin.eof())
  {
    using inputIt = std::istream_iterator< kumekova::DataStruct >;
    std::copy(inputIt{ std::cin }, inputIt{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  data.sort();

  using outputIt = std::ostream_iterator< kumekova::DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputIt{ std::cout, "\n" });
  return 0;
}
