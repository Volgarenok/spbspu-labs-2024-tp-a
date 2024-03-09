#include <iostream>
#include <limits>
#include <string>

#include "dataStruct.hpp"
#include "delimiter.hpp"

int main()
{
  using del = zagrivnyy::DelimiterI;
  using aDel = zagrivnyy::AnyCaseDelimiterI;
  std::string test = "";
  while (!(std::cin >> del{"(:"} >> test >> aDel{"GG1G"}))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  // clang-format off
  zagrivnyy::DataStruct data{'a', {-1.0, 1.0},"Hello!"};
  // clang-format on

  std::cout << test << " " << data << "\n";
  return 0;
}
