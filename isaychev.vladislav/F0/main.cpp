#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 2)
  {
    return 1;
  }
  std::map< std::string, FreqList > col;
  try
  {
    make_freqlist(std::cin, col);
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
    return 2;
  }
  const auto & c = (*col.find("text")).second;
  for (auto i = c.list.begin(); i != c.list.end(); ++i)
  {
    std::cout << (*i).first << ' ' << (*i).second;
    std::cout << '\n';
  }
}
