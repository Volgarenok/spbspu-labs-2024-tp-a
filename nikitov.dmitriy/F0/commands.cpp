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
  bool isFirst = true;

  while (fileInput >> line)
  {
    std::string temp = line;
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
      *i = std::tolower(*i);
    }
    if (!isFirst)
    {
      fileOutput << ' ';
    }
    isFirst = false;

    symb = ' ';
    try
    {
      if (!std::isalpha(temp.back()))
      {
        symb = temp.back();
        temp.pop_back();
        line.pop_back();
      }
      fileOutput << dictOfDicts.at(dictionaryName).getTranslation(temp);
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