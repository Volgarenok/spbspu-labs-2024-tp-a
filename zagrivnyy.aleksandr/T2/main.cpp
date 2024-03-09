#include <iostream>
#include <limits>
#include <string>

#include "delimiter.hpp"

// [CHR LIT] [CMP LSP]
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

  std::cout << test << "\n";
  return 0;
}
