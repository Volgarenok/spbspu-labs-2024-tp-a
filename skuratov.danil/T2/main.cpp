#include <limits>
#include <list>
#include <iterator>
#include <algorithm>

#include "delimiter.hpp"
#include "dataStruct.hpp"

int main()
{
  using namespace skuratov;
  using inputItT = std::istream_iterator< DataStruct >;
  std::list < DataStruct > d(inputItT{ std::cin }, inputItT{});
  while (!(std::cin.eof()))
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(d));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  d.sort();
  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(d.cbegin(), d.cend(), outputItT{ std::cout, "\n" });
}
