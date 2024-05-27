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