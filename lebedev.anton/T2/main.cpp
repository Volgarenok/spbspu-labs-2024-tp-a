#include <vector>
#include "data_struct.hpp"

int main()
{
  using namespace lebedev;
  using input_iter = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(input_iter{ std::cin }, input_iter{}, std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
