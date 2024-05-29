#include "arguements.hpp"
#include <fstream>

bool chernikova::processArguements(char* argv[], int argc, std::map< std::string, Dictionary >& dataBase)
{
  if (argc > 2)
  {
    printError();
    return false;
  }

  if (argc == 2)
  {
    std::string parameter = argv[1];

    if (parameter == "[dictionary]")
    {
      fillDictionary(dataBase);
    }
    else if (parameter == "--help")
    {
      printHelp();
    }
    else if (parameter == "--check")
    {
      if (isFileCorrect())
      {
        std::cout << "File is correct\n";
      }
      else
      {
        std::cout << "File is NOT correct\n";
      }
    }
    else
    {
      printError();
      return false;
    }
  }
  return true;
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
