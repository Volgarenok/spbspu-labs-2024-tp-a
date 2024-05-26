#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "utils.hpp"

int main()
{
  using namespace petrov;
  setType alph(comparePair);

  std::ifstream in("test.txt", std::ios::in);
  using isIt = std::istream_iterator< char >;
  auto addToAlph = std::bind(&addToSet, std::ref(alph), std::placeholders::_1);
  std::for_each(isIt(in), isIt(), addToAlph);
  in.close();

  using outIt = std::ostream_iterator< pairType >;
  std::copy(alph.cbegin(), alph.cend(), outIt(std::cout, "\n"));

  return 0;
}
