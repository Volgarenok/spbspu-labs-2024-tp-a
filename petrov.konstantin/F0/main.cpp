#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "HuffmanCoding.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<BRUH>\n";
    return 1;
  }

  using namespace petrov;
  std::ifstream in(argv[1], std::ios::in);
  setType alph(compareNodes);
  HuffmanCoding hc;
  hc.autoCodes(alph, in);
  in.close();

  using outIt = std::ostream_iterator< Node >;
  std::copy(alph.cbegin(), alph.cend(), outIt(std::cout, "\n"));

  return 0;
}
