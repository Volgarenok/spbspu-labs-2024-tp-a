#include "dataStruct.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

using namespace timchishina;
int main()
{
  std::vector< DataStruct > data;
  using inputIterator = std::istream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
     std::copy(inputIterator{std::cin}, inputIterator{}, std::back_inserter(data));
     if (!std::cin)
     {
       std::cin.clear();
       std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
     }
  }
  std::sort(data.begin(), data.end());
  using outputIterator = std::ostream_iterator< DataStruct >;
  std::copy(data.begin(), data.end(), outputIterator(std::cout, "\n"));
  return 0;
}
