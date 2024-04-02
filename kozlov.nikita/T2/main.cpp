#include "dataStruct.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

using namespace kozlov;
int main()
{
  std::vector< DataStruct > data;
  using inIterator = std::istream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
     std::copy(inIterator{std::cin}, inIterator{}, std::back_inserter(data));
     if (!std::cin)
     {
       std::cin.clear();
       std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
     }
  }
  std::sort(data.begin(), data.end());
  using outIterator = std::ostream_iterator< DataStruct >;
  std::copy(data.begin(), data.end(), outIterator(std::cout, "\n"));
  return 0;
}
