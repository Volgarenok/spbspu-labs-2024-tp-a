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
  using data_list = std::list<DataStruct>;
  using input = std::istream_iterator<DataStruct>;
  using output = std::ostream_iterator<DataStruct>;

  data_list data(input{ std::cin }, input{});

  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
    std::copy(input{ std::cin }, input{}, std::back_inserter(data));
  }

  std::copy(data.cbegin(), data.cend(), output{ std::cout, "\n" });
}
//(:key1 #c(1.0 -1.0):key2 (:N -1:D 5:):key3 "data":)
//(:key1 50.0d:key2 #c(1.0 -1.0):key3 "data":)
