#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"
#include "delimeter.hpp"

int main()
{
  using namespace isaychev;
  using in_it_t = std::istream_iterator< DataStruct >;
  using out_it_t = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > vec{};
  while (!std::cin.eof())
  {
    std::copy(in_it_t{std::cin}, in_it_t{}, std::back_inserter(vec));
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(vec.begin(), vec.end());
  std::copy(vec.cbegin(), vec.cend(), out_it_t{std::cout, "\n"});
}
