#include <list>
#include <iostream>
#include <limits>
#include <iterator>
#include "dataStruct.hpp"
#include "delimiter.hpp"


int main()
{
  using namespace zakozhurnikova;
//  using inputItT = std::istream_iterator< DataStruct >;

  std::list< DataStruct > data;

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
//    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
  }
}
