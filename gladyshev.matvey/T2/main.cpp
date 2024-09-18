#include <iostream>
#include <iterator>
#include <list>
#include <limits>

#include "datastruct.hpp"

int main()
{
  using namespace gladyshev;
  std::list< DataStruct > structures;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< DataStruct >{std::cin},
      std::istream_iterator< DataStruct >{},
      std::back_inserter(structures)
    );
  }
  structures.sort();
  std::copy(structures.cbegin(), structures.cend(), std::ostream_iterator< DataStruct >{std::cout, "\n"});
}
