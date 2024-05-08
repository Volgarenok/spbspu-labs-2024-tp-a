#include <list>
#include <iterator>
#include <limits>
#include "DataStruct.hpp"

int main()
{
  using namespace artemev;
  using inputIt = std::istream_iterator< DataStruct >;
  using outputIt = std::ostream_iterator< DataStruct >;

  std::list< DataStruct > data{};

  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(inputIt{ std::cin }, inputIt{}, std::back_inserter(data));
  }
  data.sort();
  std::copy(data.cbegin(), data.cend(), outputIt{ std::cout, "\n" });
  return 0;
}
