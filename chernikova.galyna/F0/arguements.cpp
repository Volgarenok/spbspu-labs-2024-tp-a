#include "arguements.hpp"

bool chernikova::processArguements(char* argv[], int argc, std::map< std::string, Dictionary >& dataBase)
{

}

void chernikova::fillDictionary(std::map< std::string, Dictionary >& dataBase)
{
  std::ifstream file("dictionary");

  if (!file.is_open())
  {
    return;
  }

  Dictionary dictionary;
  if (dictionary.read(file))
  {
    dataBase["dictionary"] = dictionary;
  }
}
