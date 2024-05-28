#include "commands.hpp"
#include <functional>
#include <fstream>
#include <Delimiter.hpp>
#include "interface.hpp"

void chernikova::doCommand(std::map< std::string, Dictionary >& dataBase, const std::string& command)
{

}

void chernikova::readData(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string fileName = "";
  std::string dictionaryName = "";

  input >> fileName >> PunctuationI{ ' ' } >> dictionaryName >> PunctuationI{ '\n' };

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
  std::string dictionaryName = "";
  std::string fileName = "";

  input >> dictionaryName >> PunctuationI{ ' ' } >> fileName >> PunctuationI{ '\n' };

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

void chernikova::addDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName = "";

  input >> dictionaryName;

  if (!input)
  {
    handleError();
    return;
  }

  dataBase[dictionaryName].clear();

  while(!input.eof())
  {
    if (input.peek() == '\n')
    {
      input >> PunctuationI{ '\n' };
      return;
    }

    input >> PunctuationI{ ' ' };

    if (!input)
    {
      handleError();
      return;
    }

    std::string word = "";
    std::string translation = "";

    input >> word >> PunctuationI{ ' ' } >> translation;

    if (!input)
    {
      handleError();
      return;
    }

    dataBase[dictionaryName].insert(word, translation);
  }
}

void chernikova::insertWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName = "";
  std::string word = "";
  std::string translation = "";

  input >> dictionaryName >> PunctuationI{ ' ' } >> word >> PunctuationI{ ' ' } >> translation >> PunctuationI{ '\n' };

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

void chernikova::deleteWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName = "";
  std::string word = "";

  input >> dictionaryName >> PunctuationI{ ' ' } >> word >> PunctuationI{ '\n' };

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
  }
}

void chernikova::print(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName = "";

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

  if (input.peek() == '\n')
  {
    input >> PunctuationI{ '\n' };
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

  std::string word = "";

  input >> PunctuationI{ ' ' } >> word >> PunctuationI{ '\n' };

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
  }
}

void chernikova::editWord(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string dictionaryName = "";
  std::string word = "";
  std::string translation = "";

  input >> dictionaryName >> PunctuationI{ ' ' } >> word >> PunctuationI{ ' ' } >> translation >> PunctuationI{ '\n' };

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
  std::string dictionaryName = "";

  input >> dictionaryName >> PunctuationI{ '\n' };

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
  std::string dictionaryName = "";

  input >> dictionaryName >> PunctuationI{ '\n' };

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
  std::string dictionaryName1 = "";
  std::string dictionaryName2 = "";

  input >> dictionaryName1 >> PunctuationI{ ' ' } >> dictionaryName2 >> PunctuationI{ '\n' };

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
  std::string dictionaryNameRes = "";
  std::string dictionaryName1 = "";
  std::string dictionaryName2 = "";

  input >> dictionaryNameRes >> PunctuationI{ ' ' } >> dictionaryName1 >> PunctuationI{ ' ' } >> dictionaryName2 >> PunctuationI{ '\n' };

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
