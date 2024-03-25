#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"


int main()
{
  using namespace chernikova;

  std::vector< DataStruct > data;
  std::istringstream iss("{ \"key1\": 1.0d, \"key2\": \"Let madness release you\" }");

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
