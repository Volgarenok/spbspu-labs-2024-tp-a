#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

int main()
{
  using namespace erohin;
  std::list< DataStruct > data;
  DataStruct record;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::cin >> record;
    if (!std::cin.fail())
    {
      data.push_back(record);
    }
  }
  data.sort();
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
