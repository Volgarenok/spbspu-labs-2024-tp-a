#include <iostream>
#include <limits>
#include <string>
#include <complex>
#include <iterator>
#include <list>
#include <algorithm>

#include "Delimiter.hpp"
#include "DataStruct.hpp"


int main()
{
  using namespace sivkov;
  using data_list = std::list<DataStruct>;
  using input = std::istream_iterator<DataStruct>;
  using output = std::ostream_iterator<DataStruct>;

  data_list data(input{ std::cin }, input{});

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::copy(input{ std::cin }, input{}, std::back_inserter(data));
  }

  std::copy(data.cbegin(), data.cend(), output{ std::cout, "\n" });
}
