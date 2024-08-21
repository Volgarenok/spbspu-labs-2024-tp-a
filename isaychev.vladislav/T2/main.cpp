#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <iomanip>
#include "dataStruct.hpp"
#include "delimeter.hpp"

int main()
{
  using namespace isaychev;
  using inIter_t = std::istream_iterator< DataStruct >;
  using outIter_t = std::ostream_iterator< DataStruct >;

  std::vector< DataStruct > vec{};
  while (!std::cin.eof())
  {
    std::copy(inIter_t{std::cin}, inIter_t{}, std::back_inserter(vec));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(vec.begin(), vec.end());
  std::cout << std::fixed << std::setprecision(1);
  std::copy(vec.cbegin(), vec.cend(), outIter_t{std::cout, "\n"});
}
