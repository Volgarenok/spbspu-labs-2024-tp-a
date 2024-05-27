#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <fstream>
#include "dictionary.hpp"

void nikitov::printDictCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  dictOfDicts.at(dictName).printDictionary(output);
}

void nikitov::printAllCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  for (auto i = dictOfDicts.begin(); i != dictOfDicts.end(); ++i)
  {
    i->second.printDictionary(output);
  }
}

void nikitov::findTranslationCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  dictOfDicts.at(dictionaryName).printTranslation(word, output);
}

void nikitov::findAntonymCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  dictOfDicts.at(dictionaryName).printAntonym(word, output);
}

void nikitov::translateSentenceCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string line;
  char symb = ' ';
  bool isFirstWord = true;
  bool isBigSymb = true;

  while (input >> line && symb != '.')
  {
    std::string temp = line;
    isBigSymb = std::isupper(temp.front());
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
      *i = std::tolower(*i);
    }
    if (!isFirstWord)
    {
      output << ' ';
    }
    isFirstWord = false;

    symb = ' ';
    try
    {
      if (!std::isalpha(temp.back()))
      {
        symb = temp.back();
        temp.pop_back();
        line.pop_back();
      }
      temp = dictOfDicts.at(dictionaryName).getTranslation(temp);
      if (isBigSymb)
      {
        setlocale(LC_ALL, "Russian");
        temp.front() = std::toupper(temp.front());
      }
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
  std::string line;
  char symb = ' ';
  bool isFirstWord = true;
  bool isBigSymb = true;

  while (input >> line)
  {
    std::string temp = line;
    isBigSymb = std::isupper(temp.front());
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
      *i = std::tolower(*i);
    }
    if (!isFirstWord)
    {
      fileOutput << ' ';
    }
    isFirstWord = false;

    symb = ' ';
    try
    {
      if (!std::isalpha(temp.back()))
      {
        symb = temp.back();
        temp.pop_back();
        line.pop_back();
      }
      temp = dictOfDicts.at(dictionaryName).getTranslation(temp);
      if (isBigSymb)
      {
        setlocale(LC_ALL, "Russian");
        temp.front() = std::toupper(temp.front());
      }
      fileOutput << temp;
    }
    catch (const std::exception&)
    {
      fileOutput << line;
    }
    if (symb != ' ')
    {
      fileOutput << symb;
    }
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
  dictOfDicts.at(dictName).printDictionary(fileOutput);
}

void nikitov::createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  if (!dictOfDicts.insert({ dictionaryName, Dictionary() }).second)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::addTranslationCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  dictOfDicts.at(dictionaryName).addTranslation(word, translation);
}

void nikitov::addAntonymCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  dictOfDicts.at(dictionaryName).addAntonym(word, translation);
}

void nikitov::editPrimaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string translation;
  input >> translation;
  dictOfDicts.at(dictionaryName).editPrimaryTranslation(word, translation);
}

void nikitov::editSecondaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string translation;
  input >> translation;
  dictOfDicts.at(dictionaryName).editSecondaryTranslation(word, translation);
}

void nikitov::deletePrimaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  dictOfDicts.at(dictionaryName).deletePrimaryTranslation(word);
}

void nikitov::deleteSecondaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  dictOfDicts.at(dictionaryName).deleteSecondaryTranslation(word);
}

void nikitov::deleteAntonymCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  dictOfDicts.at(dictionaryName).deleteAntonym(word);
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