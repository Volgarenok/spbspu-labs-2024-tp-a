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

void belokurskaya::cmd::add(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    EngRusDict& dict = EngRusDicts.at(name);
    if (dict.containsTranslation(key, translation))
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
    else
    {
      dict.addTranslation(key, translation);
    }
  }
  catch (const std::invalid_argument&)
  {
    EngRusDicts.at(name).addWord(key);
    EngRusDicts.at(name).addTranslation(key, translation);
  }
}

void belokurskaya::cmd::remove(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    EngRusDict& dict = EngRusDicts.at(name);

    if (dict.containsWord(key) && dict.containsTranslation(key, translation))
    {
      dict.removeTranslation(key, translation);
      dict.removeWord(key);
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

void belokurskaya::cmd::assign(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  if (EngRusDicts.find(nameSecondDict) == EngRusDicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  EngRusDicts.at(nameFirstDict).addWordFromEngRusDict(EngRusDicts[nameSecondDict]);
}

void belokurskaya::cmd::removeWords(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  if (EngRusDicts.find(nameSecondDict) == EngRusDicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  EngRusDict& firstDict = EngRusDicts.at(nameFirstDict);
  EngRusDict& secondDict = EngRusDicts.at(nameSecondDict);

  bool foundDuplicates = false;

  for (const auto& word : firstDict.getWords())
  {
    if (secondDict.containsWord(word))
    {
      firstDict.removeWord(word);
      foundDuplicates = true;
    }
  }

  if (!foundDuplicates)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void belokurskaya::cmd::getIntersection(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (EngRusDicts.find(name) != EngRusDicts.cend())
  {
    throw std::runtime_error("Use a different name");
  }
  in >> nameFirstDict >> nameSecondDict;
  if (EngRusDicts.find(nameFirstDict) == EngRusDicts.end() || EngRusDicts.find(nameSecondDict) == EngRusDicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  EngRusDict& firstDict = EngRusDicts[nameFirstDict];
  EngRusDict& secondDict = EngRusDicts[nameSecondDict];

  bool hasIntersection = false;

  for (const auto& word : firstDict.getWords())
  {
    if (secondDict.containsWord(word))
    {
      hasIntersection = true;
      break;
    }
  }

  if (!hasIntersection)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  EngRusDicts[name] = getIntersectionWithEngRusDict(EngRusDicts[nameFirstDict], EngRusDicts[nameSecondDict]);
}

void belokurskaya::cmd::getDifference(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (EngRusDicts.find(name) != EngRusDicts.cend())
  {
    throw std::runtime_error("Use a different name");
  }
  in >> nameFirstDict >> nameSecondDict;
  if (EngRusDicts.find(nameFirstDict) == EngRusDicts.end() || EngRusDicts.find(nameSecondDict) == EngRusDicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  EngRusDict& firstDict = EngRusDicts[nameFirstDict];
  EngRusDict& secondDict = EngRusDicts[nameSecondDict];

  auto uniqueWords = getDifferenceWithEngRusDict(firstDict, secondDict);

  if (uniqueWords.getCountWords() == 0)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  EngRusDicts[name] = uniqueWords;
}

void belokurskaya::cmd::clear(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  EngRusDicts.at(name).clear();
}

void belokurskaya::cmd::display(std::unordered_map< std::string, EngRusDict >& EngRusDicts,
  std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;

  if (EngRusDicts.find(dictName) == EngRusDicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  else
  {
    EngRusDicts[dictName].display(out);
  }
}

void belokurskaya::cmd::getTranslation(std::unordered_map< std::string, EngRusDict >& EngRusDicts,
  std::istream&, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  std::set< std::string > result;
  for (std::pair< std::string, EngRusDict > pair : EngRusDicts)
  {
    try
    {
      const auto& tr = pair.second.getTranslations(key);
      result.insert(tr.begin(), tr.end());
    }
    catch (const std::out_of_range&)
    {
      continue;
    }
  }
  if (result.size() == 0)
  {
    throw std::runtime_error("There are no translations");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void belokurskaya::cmd::countTranslations(std::unordered_map< std::string,
  EngRusDict >& EngRusDicts, std::istream& in, std::ostream& out)
{
  std::string name, key;
  in >> name >> key;
  if (EngRusDicts.find(name) == EngRusDicts.end() || !EngRusDicts[name].containsWord(key))
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  else
  {
    std::set<std::string> translations = EngRusDicts[name].getTranslations(key);
    out << translations.size() << "\n";
    std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, "\n"));
  }
}

void belokurskaya::cmd::help(std::ostream& out)
{
  out << "add <dictionary> <key> <translation>\n";
  out << "remove <dictionary> <key> <translation>\n";
  out << "createDict <new dictionary>\n";
  out << "removeDict <dictionary>\n";
  out << "assign <dictionary1> <dictionary2>\n";
  out << "removeWords <dictionary1> <dictionary2>\n";
  out << "getTranslation <key>\n";
  out << "countTranslations <dictionary> <key>\n";
  out << "getIntersection <new dictionary> <dictionary1> <dictionary2>\n";
  out << "getDifference <new dictionary> <dictionary1> <dictionary2>\n";
  out << "clear <dictionary>\n";
  out << "display <dictionary>\n";
}

void belokurskaya::cmd::checkFile(std::istream& in, std::ostream& out)
{
  std::string filename;
  in >> filename;
  std::ifstream file(filename);
  if (file.good())
  {
    out << "File exists and is accessible\n";
  }
  else
  {
    out << "File does not exist or is not accessible\n";
  }
}
