#include "commands.hpp"
#include <functional>
#include "dictionary.hpp"

void nikitov::printCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;

  if (dictName != "all")
  {
    auto value = dictOfDicts.find(dictName);
    if (value != dictOfDicts.cend())
    {
      value->second.printDictionary(output);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else
  {
    for (auto i = dictOfDicts.begin(); i != dictOfDicts.end(); ++i)
    {
      i->second.printDictionary(output);
    }
  }
}

void nikitov::addCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  if (parameter == "translation")
  {
    dictOfDicts.at(dictionaryName).addTranslation(word, translation);
  }
  else if (parameter == "antonym")
  {
    dictOfDicts.at(dictionaryName).addAntonym(word, translation);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::editCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string type;
  input >> type;
  if (parameter != "translation")
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string translation;
  input >> translation;
  if (type == "primary")
  {
    dictOfDicts.at(dictionaryName).editPrimaryTranslation(word, translation);
  }
  else if (type == "secondary")
  {
    dictOfDicts.at(dictionaryName).editSecondaryTranslation(word, translation);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::deleteCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "translation")
  {
    std::string type;
    input >> type;
    if (type == "primary")
    {
      dictOfDicts.at(dictionaryName).deletePrimaryTranslation(word);
    }
    else if (type == "secondary")
    {
      dictOfDicts.at(dictionaryName).deleteSecondaryTranslation(word);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else if (parameter == "antonym")
  {
    dictOfDicts.at(dictionaryName).deleteAntonym(word);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  if (parameter == "dictionary")
  {
    if (!dictOfDicts.insert({ dictionaryName, Dictionary() }).second)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}