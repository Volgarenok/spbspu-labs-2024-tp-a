#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "freqList.hpp"

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
  FreqList l;
  Word w;
  while (input)
  {
    input >> w;
    l.insert(w);
    if (input.eof())
    {
      break;
    }
    if (input.fail())
    {
      input.clear();
    }
  }
  for (auto i = l.list.begin(); i != l.list.end(); ++i)
  {
    std::cout << (*i).first << ' ' << (*i).second;
    std::cout << '\n';
  }
}
