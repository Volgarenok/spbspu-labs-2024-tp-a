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
  DataStruct temp;

  while (std::cin >> temp)
  {
    data.push_back(temp);
  }

  if (!std::cin.eof())
  {
    std::cin.clear();
  }

  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< DataStruct >(std::cout, "\n"));
}
