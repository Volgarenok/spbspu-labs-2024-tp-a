#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>

#include "dataStruct.hpp"

int main()
{
  std::vector< zhalilov::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< zhalilov::DataStruct >(std::cin),
      std::istream_iterator< zhalilov::DataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< zhalilov::DataStruct >(std::cout, "\n")
  );
}
