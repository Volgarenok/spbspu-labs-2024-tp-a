#include <vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include "DataStruct.hpp"

int main()
{
  std::vector< kozakova::DataStruct > data{};
  using inputItT = std::istream_iterator< kozakova::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  using outputItT = std::ostream_iterator< kozakova::DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
  return 0;
}