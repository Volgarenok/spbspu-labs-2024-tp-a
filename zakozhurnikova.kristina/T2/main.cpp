#include "DataStruct.hpp"
#include "Delimeter.hpp"

int main()
{
  using namespase zakozhurnikova;
  std::list< DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

}
