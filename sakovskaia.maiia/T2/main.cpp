#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

using namespace sakovskaia;
int main()
{
  std::vector<DataStruct> data_struct;
  std::cerr << "Start reading data..." << std::endl;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator<DataStruct>{std::cin}, std::istream_iterator<DataStruct>{}, std::back_inserter(data_struct));
    if (!std::cin)
    {
      std::cerr << "Error occurred during input. Clearing state and ignoring remaining input." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
  }
  std::cerr << "Sorting data..." << std::endl;
  std::sort(data_struct.begin(), data_struct.end());
  std::cerr << "Outputting data..." << std::endl;
  std::copy(data_struct.cbegin(), data_struct.cend(), std::ostream_iterator<DataStruct>{std::cout, "\n"});
  std::cerr << "Done." << std::endl;
}
