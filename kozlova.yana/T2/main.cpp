#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using namespace kozlova;

  std::vector< DataStruct > dataStruct;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< DataStruct >{std::cin},
      std::istream_iterator< DataStruct >{},
      std::back_inserter(dataStruct)
    );

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(dataStruct.begin(), dataStruct.end());
  std::copy(
    dataStruct.begin(),
    dataStruct.end(),
    std::ostream_iterator< DataStruct >{std::cout, "\n"}
  );

  return 0;
}
