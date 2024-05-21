#include <list>
#include <iterator>

#include "delimiter.hpp"
#include "dataStruct.hpp"

int main()
{
  using namespace skuratov;
  using inputItT = std::istream_iterator< DataStruct >;
  std::list< DataStruct > data(inputItT{ std::cin }, inputItT{});
  while (!(std::cin.eof()))
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  data.sort();
  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
}
