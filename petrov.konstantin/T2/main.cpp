
#include <iostream>
#include <string>
#include <sstream>
#include "DataStruct.h"

void input_manual_test();
bool input_tests();

int main()
{
  //input_manual_test();
  std::cout << std::boolalpha << input_tests();
  return 0;
}

void input_manual_test()
{
  petrov::DataStruct ds(0, 0, "default");
  std::cin >> ds;
  std::cout << ds.key1_ << ' ' << ds.key2_ << ' ' << ds.key3_ << '\n';
}

bool input_tests()
{
  bool fl = true;
  petrov::DataStruct ds(0, 0, "default");
  std::istringstream iss("(:key1 -89LL:key2 0b0101:key3 \"someThing\":)");
  iss >> ds;
  //std::cout << "(:key1 -89LL:key2 0b0101:key3 \"something\":)\n";
  std::cout << ds;
  //std::cout << ds.key1_ << ' ' << ds.key2_ << ' ' << ds.key3_ << '\n';
  fl = ((ds.key1_ == -89) && (ds.key2_ == 5));

  std::istringstream iss2("(:key1 1929ll:key2 0B0000101:key3 \"hello\":)");
  iss2 >> ds;
  //std::cout << "(:key1 1929ll:key2 0B0000101:\"hello\"\n";
  std::cout << ds;
  //std::cout << ds.key1_ << ' ' << ds.key2_ << ' ' << ds.key3_ << '\n';
  fl = ((ds.key1_ == 1929) && (ds.key2_ == 5));

  return fl;
}