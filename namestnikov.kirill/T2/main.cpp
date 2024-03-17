#include <iostream>
#include <string>
#include <limits>
#include "delimeters.hpp"
#include "data_struct.hpp"

int main()
{
  using namespace namestnikov;
  DataStruct d(0, 0, "");
  if (!(std::cin >> d))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!(std::cin >> d))
    {
      std::cerr << "Error\n";
      return 1;
    }
  }
}