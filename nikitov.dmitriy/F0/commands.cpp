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
  bool isFirst = true;
  while (input >> line)
  {
    for (auto i = line.begin(); i != line.end(); ++i)
    {
      *i = std::tolower(*i);
    }
    if (isFirst)
    {
      isFirst = false;
    }
    else if (!isFirst)
    {
      output << ' ';
    }
    try
    {
      if (line.back() == '.')
      {
        std::string temp = line;
        temp.pop_back();
        output << dictOfDicts.at(dictionaryName).getTranslation(temp);
        break;
      }
      else
      {
        output << dictOfDicts.at(dictionaryName).getTranslation(line);
      }
    }
    catch (const std::exception&)
    {
      if (line.back() == '.')
      {
        line.pop_back();
        output << line;
        break;
      }
      else
      {
        output << line;
      }
    }
  }
  output << '.' << '\n';
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
  bool isFirst = true;
  while (fileInput >> line)
  {
    for (auto i = line.begin(); i != line.end(); ++i)
    {
      *i = std::tolower(*i);
    }
    if (isFirst)
    {
      isFirst = false;
    }
    else if (!isFirst)
    {
      fileOutput << ' ';
    }
    try
    {
      if (line.back() == '.')
      {
        std::string temp = line;
        temp.pop_back();
        fileOutput << dictOfDicts.at(dictionaryName).getTranslation(temp);
      }
      else
      {
        fileOutput << dictOfDicts.at(dictionaryName).getTranslation(line);
      }
    }
    catch (const std::exception&)
    {
      if (line.back() == '.')
      {
        line.pop_back();
        fileOutput << line;
      }
      else
      {
        fileOutput << line;
      }
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