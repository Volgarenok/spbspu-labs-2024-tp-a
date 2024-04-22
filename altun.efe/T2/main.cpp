#include <iostream>
#include <iomanip>
#include <string>
#include <ios>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "streamGuard.hpp"
#include "delimiter.hpp"
#include "dataStruct.hpp"

int main()
{
  using namespace altun;
  DataStruct a{0, 0, ""};
  std::cin >> a;
  std::cout << a << '\n';
}
