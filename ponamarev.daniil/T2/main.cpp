#include "DataStruct.h"
#include "Delimeter.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>

int main()
{
  std::vector< ponamarev::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< ponamarev::DataStruct >(std::cin),
      std::istream_iterator< ponamarev::DataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(std::begin(data), std::end(data), std::ostream_iterator< ponamarev::DataStruct >(std::cout, "\n"));
  return 0;
}
