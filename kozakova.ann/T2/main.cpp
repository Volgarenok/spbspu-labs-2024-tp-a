#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  std::list< kozakova::DataStruct > data{};
  while (!std::cin.eof())
  {
    using inputItT = std::istream_iterator< kozakova::DataStruct >;
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  data.sort();

  using outputItT = std::ostream_iterator< kozakova::DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
  return 0;
}
