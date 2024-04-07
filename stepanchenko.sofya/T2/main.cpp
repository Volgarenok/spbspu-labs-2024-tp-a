#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

#include "DataStruct.h"

int main()
{
  using namespace stepanchenko;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
	std::istream_iterator< DataStruct >{std::cin},
	std::istream_iterator< DataStruct >(),
	std::back_inserter(data)
    );
  }

  std::sort(data.begin(), data.end());
  std::copy(
	data.begin(),
	data.end(),
	std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
