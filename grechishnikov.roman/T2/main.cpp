#include <iostream>
#include "dataStruct.hpp"

int main()
{
  using namespace grechishnikov;

  DataStruct a { 10, { 3.1, 3.003 }, "aaa" };
  std::cout << a << '\n';
}
