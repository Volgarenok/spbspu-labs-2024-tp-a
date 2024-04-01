#include <iostream>
#include "dataStruct.hpp"

int main()
{
  using namespace grechishnikov;

  DataStruct a { 10, { 3, 3 }, "aaa" };
  std::cout << a << '\n';
}
