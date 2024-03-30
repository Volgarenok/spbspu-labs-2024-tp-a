#include <ios>
#include <iterator>
#include <limits>
#include <vector>
#include "dataStructure.hpp"

int main()
{
  using namespace ibragimov;
  using is_iterator = std::istream_iterator<DataStructure>;
  using os_iterator = std::ostream_iterator<DataStructure>;

  std::vector<DataStructure> data;
  while (!std::cin.eof()) {
    std::copy(is_iterator{std::cin}, is_iterator{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::copy(std::begin(data), std::end(data), os_iterator(std::cout, "\n"));

  return 0;
}
