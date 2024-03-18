#include <list>
#include <iostream>
#include <limits>
#include "dataStruct.hpp"
#include "delimiter.hpp"


int main()
{
  using namespace zakozhurnikova;
  std::list< DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
