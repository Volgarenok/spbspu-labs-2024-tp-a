#include "readDictionary.hpp"

std::vector< belokurskaya::EngRusDict > belokurskaya::ReadEngRusDictFromFile(std::string pathToFile)
{
  std::ifstream file(pathToFile);
  if (!file.is_open())
  {
    throw std::invalid_argument("Error with reading dictionary");
  }
  std::vector< EngRusDict > EngRusDicts;
  std::string name;
  while (getline(file, name))
  {
    EngRusDict newErd(name);
    std::string words;
    while (std::getline(file, words) && !words.empty())
    {
      std::stringstream ss(words);
      std::string eng, rus;
      std::getline(ss, eng, ':');
      try
      {
        newErd.addWord(eng);
      }
      catch (const std::invalid_argument&)
      {
        continue;
      }
      try
      {
        while (std::getline(ss, rus, ',') && !rus.empty())
        {
          rus.erase(0, 1);
          newErd.addTranslation(eng, rus);
        }
      }
      catch (const std::invalid_argument&)
      {
        newErd.removeWord(eng);
      }
    }
    EngRusDicts.push_back(newErd);
  }
  file.close();
  return EngRusDicts;
}