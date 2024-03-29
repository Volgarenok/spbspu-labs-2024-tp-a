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
    std::copy
    (
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(dataStruct)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore
      (
        std::numeric_limits<std::streamsize>::max(),
        '\n'
      );
    }
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

