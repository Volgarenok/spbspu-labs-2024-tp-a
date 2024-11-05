#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "delimiters.hpp"
#include "datastruct.hpp"

int main()
{
  using namespace petuhov;

  std::vector< DataStruct > data;
  std::copy(std::istream_iterator< DataStruct >(std::cin), std::istream_iterator< DataStruct >(), std::back_inserter(data));

  if (std::cin.bad()) {
    return 1;
  }
  if (std::cin.fail() && !std::cin.eof()) {
    std::cin.clear();
  }

  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< DataStruct >(std::cout, "\n"));
}
