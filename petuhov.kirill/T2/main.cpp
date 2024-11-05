#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "delimiters.hpp"
#include "datastruct.hpp"

int main()
{
  using namespace petuhov;

  std::vector< DataStruct > data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    DataStruct temp;

    if (iss >> temp)
    {
      data.push_back(temp);
    }
    else
    {
      std::cin.clear();
    }
  }

  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< DataStruct >(std::cout, "\n"));
}
