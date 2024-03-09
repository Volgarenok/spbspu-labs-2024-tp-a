#include <iostream>
#include <limits>
#include <string>

#include "delimiter.hpp"

// [CHR LIT] [CMP LSP]
int main()
{
  using del = zagrivnyy::DelimiterI;
  std::string test = "";
  while (!(std::cin >> del{"(:"} >> test))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::cout << test << "\n";
  return 0;
}
