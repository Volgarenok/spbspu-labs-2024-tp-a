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

  std::vector<DataStruct> data;
  DataStruct temp;

  while (true)
  {
    if (std::cin >> temp)
    {
      data.push_back(temp);
    }
    else
    {
      if (std::cin.eof())
      {
        break;
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
