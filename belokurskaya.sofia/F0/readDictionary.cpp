#include "readDictionary.hpp"

std::unordered_map< std::string, belokurskaya::EngRusDict >
  belokurskaya::ReadEngRusDictFromFile(const std::string& pathToFile)
{
  std::ifstream file(pathToFile);
  if (!file.is_open())
  {
    throw std::invalid_argument("Error with reading dictionary");
  }
  std::unordered_map< std::string, EngRusDict > EngRusDicts;
  std::string name;
  while (getline(file, name))
  {
    EngRusDict newErd;
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
    EngRusDicts[name] = newErd;
  }
  file.close();
  return EngRusDicts;
}
