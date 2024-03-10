#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <string>
#include <bitset>
#include "dataStruct.hpp"

int main()
{
  unsigned long long s = 100;
  std::bitset<64> bin(s);
  std::cout << bin << '\n';
}
