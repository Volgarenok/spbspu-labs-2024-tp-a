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

  while (std::cin)
  {
    DataStruct item;

    if (std::cin >> item)
    {
      data.push_back(item);
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  for (std::vector< DataStruct >::const_iterator it = data.cbegin(); it != data.cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  return 0;
}
