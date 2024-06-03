#include "commands.hpp"
#include <fstream>
#include <delimiter.hpp>
#include <interface.hpp>
#include <streamGuard.hpp>

chernikova::Commands chernikova::initializeCommands()
{
  Commands commandsSet;

  commandsSet.insert({ "readData", readData });
  commandsSet.insert({ "saveData", saveData });
  commandsSet.insert({ "addDictionary", addDictionary });
  commandsSet.insert({ "insertWord", insertWord });
  commandsSet.insert({ "forceInsertWords", forceInsertWords });
  commandsSet.insert({ "forceInsertLine", forceInsertLine });
  commandsSet.insert({ "deleteWord", deleteWord });
  commandsSet.insert({ "print", print });
  commandsSet.insert({ "editWord", editWord });
  commandsSet.insert({ "clearDictionary", clearDictionary });
  commandsSet.insert({ "getNumberWords", getNumberWords });
  commandsSet.insert({ "merge", merge });
  commandsSet.insert({ "intersection", intersection });

  return commandsSet;
}

bool chernikova::doCommand(std::map< std::string, Dictionary >& dataBase)
{
  StreamGuard streamGuard(std::cin);
  std::cin.unsetf(std::ios_base::skipws);

  static Commands functions = initializeCommands();

  std::string command;
  std::cin >> command;

  if (std::cin.eof())
  {
    return false;
  }

  if (!std::cin)
  {
    handleError();
    return true;
  }

  std::cin >> ExactSymbolI{ ' ' };

  if (!std::cin)
  {
    handleError();
    return true;
  }

  try
  {
    functions.at(command)(dataBase, std::cin);
  }
  catch (const std::out_of_range& error)
  {
    handleError();
    return true;
  }

  return true;
}

void chernikova::readData(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string fileName;
  std::string dictionaryName;
  input >> fileName >> ExactSymbolI{ ' ' } >> dictionaryName >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    printError();
    return;
  }

  dataBase[dictionaryName].read(file);
}

void chernikova::saveData(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  std::string fileName;
  input >> dictionaryName >> ExactSymbolI{ ' ' } >> fileName >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  if (iterator->second.getSize() == 0)
  {
    printEmptyError();
    return;
  }

  std::ofstream file(fileName);
  if (!file.is_open())
  {
    printError();
    return;
  }

  iterator->second.print(file);
}

void chernikova::addDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input) //FIXME
{
  std::string dictionaryName;
  input >> dictionaryName >> ExactSymbolI{ '\n' };

  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);

  if (iterator != dataBase.end())
  {
    printError();
    return;
  }

  dataBase[dictionaryName] = {};
}

void chernikova::insertWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  std::string word;
  std::string translation;
  input >> dictionaryName >> ExactSymbolI{ ' ' } >> word >> ExactSymbolI{ ' ' } >> translation >> ExactSymbolI{ '\n' };

  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  if (!iterator->second.insert(word, translation))
  {
    printError();
  }
}

void chernikova::forceInsertWords(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName >> ExactSymbolI{ ' ' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  std::string word;
  std::string translation;
  char delimeter = 0;
  input >> word >> ExactSymbolI{ ' ' } >> translation >> AnySymbolI{ " \n", delimeter };
  if (!input)
  {
    handleError();
    return;
  }

  iterator->second.insert(word, translation);

  while (delimeter != '\n')
  {
    input >> word >> ExactSymbolI{ ' ' } >> translation >> AnySymbolI{ " \n", delimeter };

    if (!input)
    {
      handleError();
      return;
    }

    iterator->second.insert(word, translation);
  }

  if (!input)
  {
    handleError();
    return;
  }
}

void chernikova::forceInsertLine(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName >> ExactSymbolI{ ' ' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  std::string word;
  std::string translation;
  char delimeter = 0;
  input >> word >> ExactSymbolI{ ' ' } >> translation >> AnySymbolI{ " \n", delimeter };
  iterator->second.insert(word, translation);
  if (!input)
  {
    handleError();
    return;
  }

  while (delimeter != '\n')
  {
    input >> translation >> AnySymbolI{ " \n", delimeter };

    if (!input)
    {
      handleError();
      return;
    }

    iterator->second.insert(word, translation);
  }

  if (!input)
  {
    handleError();
    return;
  }
}

void chernikova::deleteWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  std::string word;
  input >> dictionaryName >> ExactSymbolI{ ' ' } >> word >> ExactSymbolI{ '\n' };

  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  if (!iterator->second.erase(word))
  {
    printError();
    return;
  }
}

void chernikova::print(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;

  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  char delimeter = 0;
  input >> AnySymbolI{ " \n", delimeter };

  if (delimeter == '\n')
  {
    if (iterator->second.getSize() == 0)
    {
      printEmptyError();
    }
    else
    {
      iterator->second.print(std::cout);
    }
    return;
  }

  std::string word;
  input >> word >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  int code = iterator->second.print(std::cout, word);

  if (code == 1)
  {
    printError();
    return;
  }
  if (code == 2)
  {
    printEmptyError();
    return;
  }
}

void chernikova::editWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  std::string word;
  std::string translation;
  input >> dictionaryName >> ExactSymbolI{ ' ' } >> word >> ExactSymbolI{ ' ' } >> translation >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }
  if (!iterator->second.erase(word))
  {
    printError();
    return;
  }

  iterator->second.insert(word, translation);
}

void chernikova::clearDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }
  if (iterator->second.getSize() == 0)
  {
    printEmptyError();
    return;
  }

  iterator->second.clear();
}

void chernikova::getNumberWords(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator = dataBase.find(dictionaryName);
  if (iterator == dataBase.end())
  {
    printError();
    return;
  }

  std::cout << iterator->second.getSize() << std::endl;
}

void chernikova::merge(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName1;
  std::string dictionaryName2;
  input >> dictionaryName1 >> ExactSymbolI{ ' ' } >> dictionaryName2 >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator1 = dataBase.find(dictionaryName1);
  auto iterator2 = dataBase.find(dictionaryName2);
  if (iterator1 == dataBase.end() || iterator2 == dataBase.end())
  {
    printError();
    return;
  }

  iterator1->second.mergeFrom(iterator2->second);
}

void chernikova::intersection(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryNameRes;
  std::string dictionaryName1;
  std::string dictionaryName2;
  input >> dictionaryNameRes >> ExactSymbolI{ ' ' } >> dictionaryName1 >> ExactSymbolI{ ' ' } >> dictionaryName2 >> ExactSymbolI{ '\n' };
  if (!input)
  {
    handleError();
    return;
  }

  auto iterator1 = dataBase.find(dictionaryName1);
  auto iterator2 = dataBase.find(dictionaryName2);
  if (iterator1 == dataBase.end() || iterator2 == dataBase.end())
  {
    printError();
    return;
  }

  Dictionary result = iterator1->second.intersection(iterator2->second);

  if (result.getSize() == 0)
  {
    printEmptyError();
    return;
  }

  dataBase[dictionaryNameRes] = result;
}
