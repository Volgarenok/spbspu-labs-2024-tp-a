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

void chernikova::printHelp()
{
  std::cout << "HELP:\n";
  std::cout << "readData <file> <dictionary name>\n";
  std::cout << "saveData <dictionary> <file>\n";
  std::cout << "addDictionary <dictionary>\n";
  std::cout << "insertWord <dictionary> <word> <translation>\n";
  std::cout << "deleteWord <dictionary> <word>\n";
  std::cout << "print <dictionary> <word>\n";
  std::cout << "print <dictionary>\n";
  std::cout << "editWord <dictionary> <word> <new translation>\n";
  std::cout << "clearDictionary <dictionary>\n";
  std::cout << "getNumberWords <dictionary>\n";
  std::cout << "merge <dictionary1> <dictionary2>\n";
  std::cout << "getIntersection <dictionary result> <dictionary1> <dictionary2>\n";
}

bool chernikova::isFileCorrect()
{
  std::ifstream file("dictionary");

  if (!file.is_open())
  {
    return false;
  }

  Dictionary dictionary;
  return dictionary.read(file);
}
