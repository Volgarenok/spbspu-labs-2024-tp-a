#include <iostream>
#include "DataStruct.hpp"
#include "DelimiterI.hpp"

int main()
{
  using namespace kuzmina;
  DataStruct ds{ 5, {5, 5}, "555" };

  std::cin >> ds;   // (:key1 77LL:key3 "hi :":key2 (:N 8:D 9:):)
  std::cout << ds;  // (:key1 77ll:key2 (:N 8:D 9:):key3 "hi :":)

  return 0;
}
