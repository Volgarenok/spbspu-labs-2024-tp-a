#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <iterator>

#include "dataStruct.hpp"

int main()
{
  //in format -> (:key1 076:key2 'a':key3 "hiOsaka":)
  using namespace arakelyan;
  std::vector< DataStruct > data;

  while (!std::cin.eof())
  {
    std::copy(
    std::istream_iterator< DataStruct >{std::cin},
    std::istream_iterator< DataStruct >{},
    std::back_inserter(data)
    );
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  // std::copy(
  //   data.begin(),
  //   data.end(),
  //   std::ostream_iterator< DataStruct >(std::cout, "\n")
  // );

  auto it = data.begin();
  while (it != data.cend())
  {
    std::cout << *it << "\n";
    ++it;
  }
  // std::cout << *data.begin() << "\n";

  return 0;
}
