#include <list>
#include <iostream>
#include <string>
#include <limits>
#include <iterator>
#include <algorithm>
#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "scopeGuard.hpp"

int main()
{
  using namespace zakozhurnikova;
  using inputItT = std::istream_iterator< DataStruct >;

  std::list< DataStruct > data(inputItT{std::cin}, inputItT{});

  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
  }
  data.sort();
  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{std::cout, "\n"});
}
