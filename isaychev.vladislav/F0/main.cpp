#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "word.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 2)
  {
    return 1;
  }
  std::vector< Word > fl;
  using input_iter_t = std::istream_iterator< Word >;
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "bad file\n";
    return 2;
  }
  while (input)
  {
    std::copy(input_iter_t{input}, input_iter_t{}, std::back_inserter(fl));
    if (input.eof())
    {
      break;
    }
    if (input.fail())
    {
      input.clear();
    }
  }
  for (auto i = fl.begin(); i != fl.end(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
}
