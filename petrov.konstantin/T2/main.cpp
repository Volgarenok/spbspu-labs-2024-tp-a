#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

int main()
{
  using petrov::DataStruct;
  std::vector< DataStruct > dataStruct;
  while (!std::cin.eof())
  {
    std::cin.setstate(std::ios::goodbit);
    std::copy
    (
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(dataStruct)
    );
  }
  std::sort
  (
    dataStruct.begin(),
    dataStruct.end()
  );
  std::copy
  (
    std::begin(dataStruct),
    std::end(dataStruct),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
