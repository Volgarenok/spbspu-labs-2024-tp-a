#include "commands.hpp"

#include <functional>
#include <algorithm>

#include "readDictionary.hpp"

void belokurskaya::cmd::createDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (EngRusDicts.find(name) != EngRusDicts.cend())
  {
    throw std::runtime_error("Use a different name");
  }
  EngRusDicts[name] = EngRusDict();
}

void belokurskaya::cmd::removeDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (EngRusDicts.find(name) == EngRusDicts.cend())
  {
    throw std::runtime_error("There is no dictionary with that name");
  }
  EngRusDicts.erase(name);
}

void belokurskaya::cmd::add(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    EngRusDict& dict = vector.at(name);
    if (dict.containsTranslation(key, translation))
    {
      std::cerr << "<INVALID COMMAND>";
    }
    else
    {
      dict.addTranslation(key, translation);
    }
  }
  catch (const std::invalid_argument&)
  {
    vector.at(name).addWord(key);
    vector.at(name).addTranslation(key, translation);
  }
}

void belokurskaya::cmd::remove(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    EngRusDict& dict = vector.at(name);

    if (dict.containsWord(key) && dict.containsTranslation(key, translation))
    {
      dict.removeTranslation(key, translation);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>";
    }
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<INVALID COMMAND>";
  }
}

void belokurskaya::cmd::assign(std::unordered_map<std::string, EngRusDict>& vector, std::istream& in) {
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  if (vector.find(nameSecondDict) == vector.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  vector.at(nameFirstDict).addWordFromEngRusDict(vector[nameSecondDict]);
}

void belokurskaya::cmd::removeWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  if (vector.find(nameSecondDict) == vector.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  EngRusDict& firstDict = vector.at(nameFirstDict);
  EngRusDict& secondDict = vector.at(nameSecondDict);

  bool foundDuplicates = false;

  for (const auto& word : firstDict.getWords())
  {
    if (secondDict.containsWord(word)) {
      firstDict.removeWord(word);
      foundDuplicates = true;
    }
  }

  if (!foundDuplicates)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void belokurskaya::cmd::getIntersection(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.find(name) != vector.cend())
  {
    throw std::runtime_error("Use a different name");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector[name] = getIntersectionWithEngRusDict(vector[nameFirstDict], vector[nameSecondDict]);
}

void belokurskaya::cmd::getDifference(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.find(name) != vector.cend())
  {
    throw std::runtime_error("Use a different name");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector[name] = getDifferenceWithEngRusDict(vector[nameFirstDict], vector[nameSecondDict]);
}

void belokurskaya::cmd::clear(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector.at(name).clear();
}

void belokurskaya::cmd::display(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  for (std::pair< std::string, EngRusDict > pair : vector)
  {
    out << pair.first;
    pair.second.display(out);
  }
}

void belokurskaya::cmd::getTranslation(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  std::vector< std::string > result;
  for (std::pair< std::string, EngRusDict > pair : vector)
  {
    for (const std::string& translation : pair.second.getTranslations(key))
    {
      if (translation != "" && std::find(result.begin(), result.end(), translation) == result.end())
      {
        result.push_back(translation);
      }
    }
  }
  if (result.size() == 0)
  {
    throw std::runtime_error("There are no translations");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}
