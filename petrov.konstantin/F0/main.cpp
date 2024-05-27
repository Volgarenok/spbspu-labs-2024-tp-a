#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "HuffmanCoding.hpp"

#include <map>

int main(int argc, char* argv[])
{
  std::map<std::string, std::string> t;
  t["1"] = "HELLO";
  t["1"] = "GEGE";
  std::cout << t["1"] << '\n';

  // if (argc != 5)
  // {
  //   std::cerr << "<BRUH>\n";
  //   return 1;
  // }

  // using namespace petrov;
  // setType alph(compareNodes);
  // HuffmanCoding hc;
  // {
  //   std::ifstream in(argv[1], std::ios::in);
  //   std::ofstream out(argv[2], std::ios::binary);

  //   hc.autoCodes(alph, in);
  //   in.clear();
  //   in.seekg(0, std::ios::beg);

  //   hc.encode(alph, out, in);

  //   in.close();
  //   out.close();
  // }
  // std::ifstream in(argv[3], std::ios::in);
  // std::ofstream out(argv[4], std::ios::binary);
  // hc.decode(alph, out, in);
  // in.close();
  // out.close();

  // using outIt = std::ostream_iterator< Node >;
  // std::copy(alph.cbegin(), alph.cend(), outIt(std::cout, "\n"));

  return 0;
}
