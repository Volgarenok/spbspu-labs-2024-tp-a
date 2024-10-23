#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <complex>
#include <limits>
#include "DataStruct.hpp"

int main()
{
  using namespace vorobieva;
  using input_it = std::istream_iterator<DataStruct>;
  using output_it = std::ostream_iterator<DataStruct>;
  std::vector<DataStruct> data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    output_it{std::cout, "\n"}
  );
  return 0;
}
