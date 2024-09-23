#include <iostream>
#include <vector>

#include "data_struct.hpp"

int main()
{
  std::vector< kovtun::DataStruct > data;

  while (!std::cin.eof())
  {
    using input_it_t = std::istream_iterator< kovtun::DataStruct >;
    std::copy(input_it_t {std::cin},input_it_t {},std::back_inserter(data));

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using output_it_t = std::ostream_iterator< kovtun::DataStruct >;
  std::copy(data.cbegin(),data.cend(),output_it_t(std::cout, "\n"));

  return 0;
}

