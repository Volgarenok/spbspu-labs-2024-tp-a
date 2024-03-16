#include <iostream>
#include <algorithm>
#include <list>
#include <limits>
#include <bitset>
#include <iterator>
#include "dataStruct.hpp"
#include "delimiter.hpp"

int main()
{
  using namespace novokhatskiy;
  using input_it_t = std::istream_iterator<DataStruct>;
  using output_it_t = std::ostream_iterator<DataStruct>;
  std::list<DataStruct> res;
  //if (std::cin >> DelimiterString{":key"})
  //{
  //  std::cout << "all good";
  //}
  //else
  //{
  //  std::cout << "bad";
  //}
  // std::cout << std::cin.eof() << std::cin.fail();
  while (!std::cin.eof())
  {
    std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(res));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  res.sort();
  std::copy(res.cbegin(), res.cend(), output_it_t{ std::cout, "\n" });
  return 0;
}
