#include <iostream>
#include <limits>
#include <string>
#include <complex>
#include <iomanip>
#include <iterator>
#include <list>
#include <algorithm>

struct DelimiterI
{
  char expected;
};

struct DelimiterStr
{
  const char * expected;
};

struct DataStruct
{
  double key1;
  std::complex<double> key2;
  std::string key3;
};

int main()
{
}
