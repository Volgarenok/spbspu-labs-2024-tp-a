#include <iostream>
#include <string>
#include <limits>
#include <iterator>
#include <algorithm>
#include <list>
#include "data_struct.hpp"

int main()
{
  using namespace namestnikov;
  using input_iterator_t = std::istream_iterator< DataStruct >;
  std::list< DataStruct > dataList(input_iterator_t{std::cin}, input_iterator_t{});
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_iterator_t{std::cin}, input_iterator_t{}, std::back_inserter(dataList));
  }
  dataList.sort();
  using output_iterator_t = std::ostream_iterator< DataStruct >;
  std::copy(dataList.cbegin(), dataList.cend(), output_iterator_t{std::cout, "\n"});
}
