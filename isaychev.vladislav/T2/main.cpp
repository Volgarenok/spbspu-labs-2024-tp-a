#include <complex>
#include <iostream>
#include "dataStruct.hpp"

int main()
{
  using namespace isaychev;
  std::complex< double > num1(12.2, 3.0);
  std::string str = "Data";
  long long num2 = 10ll;
  DataStruct data{num2, num1, str};
  std::cout << data << "\n";
}
