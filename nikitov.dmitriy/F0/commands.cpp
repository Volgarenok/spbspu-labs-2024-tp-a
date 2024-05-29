#include "commands.hpp"
#include <fstream>
#include <functional>
#include <algorithm>
#include "dictionary.hpp"

void nikitov::printDictCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  output << dictOfDicts.at(dictName);
}

void nikitov::printAllCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  for (auto i = dictOfDicts.begin(); i != dictOfDicts.end(); ++i)
  {
    output << i->second;
  }
}

void nikitov::printNamesCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  for (auto i = dictOfDicts.begin(); i != dictOfDicts.end(); ++i)
  {
    output << i->first << '\n';
  }
}

void nikitov::findCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output,
  const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "translation")
  {
    output << dictOfDicts.at(dictionaryName).findWord(word) << '\n';
  }
  else
  {
    output << dictOfDicts.at(dictionaryName).findAntonym(word) << '\n';
  }
}

char translate(const std::map< std::string, nikitov::Dictionary >& dictOfDicts, const std::string& dictionaryName, 
  std::istream& input, std::ostream& output)
{
  std::string line;
  input >> line;
  char symb = ' ';
  std::string temp = line;
  for (auto i = temp.begin(); i != temp.end(); ++i)
  {
    *i = std::tolower(*i);
  }

  try
  {
    if (!temp.empty() && !std::isalpha(temp.back()))
    {
      symb = temp.back();
      temp.pop_back();
      line.pop_back();
    }
    temp = dictOfDicts.at(dictionaryName).findTranslation(temp);
    output << temp;
  }
  catch (const std::exception&)
  {
    output << line;
  }
  if (symb != ' ')
  {
    output << symb;
  }
  return symb;
}

void nikitov::translateSentenceCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  char symb = ' ';
  bool isFirst = true;

  while (input && symb != '.')
  {
    if (!isFirst)
    {
      output << ' ';
    }
    isFirst = false;
    symb = translate(dictOfDicts, dictionaryName, input, output);
  }
  output << '\n';
}

void nikitov::translateFileCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string fileName;
  input >> fileName;
  std::string newFileName;
  input >> newFileName;

  std::ifstream fileInput(fileName);
  std::ofstream fileOutput(newFileName);
  bool isFirst = true;

  while (fileInput)
  {
    if (!isFirst)
    {
      fileOutput << ' ';
    }
    isFirst = false;
    translate(dictOfDicts, dictionaryName, fileInput, fileOutput);
  }
  fileOutput << '\n';
}

void nikitov::saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictName;
  input >> dictName;
  std::string newFileName;
  input >> newFileName;
  std::ofstream fileOutput(newFileName);
  fileOutput << dictOfDicts.at(dictName);
}

void nikitov::createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  if (!dictOfDicts.insert({ dictionaryName, Dictionary() }).second)
  {
    throw std::logic_error("<ERROR: ALREADY EXIST>");
  }
}

void nikitov::addCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  if (parameter == "translation")
  {
    dictOfDicts.at(dictionaryName).addTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).addAntonym(word, translation);
  }
}

void nikitov::editCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string translation;
  input >> translation;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).editPrimaryTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).editSecondaryTranslation(word, translation);
  }
}

void nikitov::deleteCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).deletePrimaryTranslation(word);
  }
  else if (parameter == "secondary")
  {
    dictOfDicts.at(dictionaryName).deleteSecondaryTranslation(word);
  }
  else
  {
    dictOfDicts.at(dictionaryName).deleteAntonym(word);
  }
}

void nikitov::mergeCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string firstDictionaryName;
  input >> firstDictionaryName;
  auto firstDict = dictOfDicts.at(firstDictionaryName);
  std::string secondDictionaryName;
  input >> secondDictionaryName;
  auto secondDict = dictOfDicts.at(secondDictionaryName);
  std::string newDictionaryName;
  input >> newDictionaryName;
  auto newDict = firstDict;
  for (auto i = secondDict.data_.cbegin(); i != secondDict.data_.cend(); ++i)
  {
    newDict.data_.insert(*i);
  }
  dictOfDicts.insert({ newDictionaryName, newDict });
}
