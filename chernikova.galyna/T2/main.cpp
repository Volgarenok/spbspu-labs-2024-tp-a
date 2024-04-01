#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "DataStruct.h"


int main()
{
  using namespace chernikova;

  std::vector< DataStruct > data;
  std::istringstream iss("(:key1 5.45e2:key2 076:key3 \"Data\":)");


  std::copy(
    std::istream_iterator< DataStruct >(iss),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
