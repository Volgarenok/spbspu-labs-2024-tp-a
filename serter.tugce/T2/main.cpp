#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

#include "dataIO.hpp"
#include "dataStruct.hpp"

int main()
{
  std::vector< serter::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator< serter::DataStruct >(std::cin), std::istream_iterator< serter::DataStruct >(), std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), std::ostream_iterator< serter::DataStruct >(std::cout, "\n"));
  return 0;
}

