#include <iostream>
#include <limits>

#include "dataStruct.hpp"

int main()
{
  //in format -> (:key1 10:key2 30)
  using namespace arakelyan;
  DataStruct data;
  // while(!(std::cin >> data))
  // {
  //   if (!(std::cin))
  //   {
  //     std::cin.clear();
  //     std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  //   }
  // }
  std::cin >> data;
  if (!std::cin)
  {
    std::cerr << "Incorrect format!\n";
    return 1;
  }
  std::cout << data << "\n";
  return 0;
}
