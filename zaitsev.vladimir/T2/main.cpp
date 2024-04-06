#include <iostream>
#include <list>
#include <limits>
#include "data_struct.hpp"

int main()
{
  using namespace zaitsev;
  using input_it = std::istream_iterator< DataStruct >;
  using output_it = std::ostream_iterator< DataStruct >;

  std::list< DataStruct > structs;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it(std::cin), input_it(), std::back_inserter(structs));
  }
  structs.sort();
  std::copy(structs.cbegin(), structs.cend(), output_it(std::cout, "\n"));
  return 0;
}
