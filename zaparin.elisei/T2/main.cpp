#include "dataStruct.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <algorithm>
#include <limits>


int main()
{
  using namespace zaparin;

  std::list< DataStruct > data;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data));

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  data.sort();

  std::copy(data.begin(), data.end(), std::ostream_iterator< DataStruct >(std::cout, "\n"));
}

