#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 3)
  {
    return 1;
  }
  std::map< std::string, FreqList > col;
  std::map< std::string, std::function< void(char *, std::map< std::string, FreqList > &) > > args;
  using namespace std::placeholders;
  try
  {
    make_freqlist(std::cin, col);
    print_descending(std::cin, std::cout, col);
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
    return 2;
  }
}
