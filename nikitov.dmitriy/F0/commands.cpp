#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <fstream>
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

void nikitov::findCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "translation")
  {
    dictOfDicts.at(dictionaryName).printTranslation(word, output);
  }
  else if (parameter == "antonym")
  {
    dictOfDicts.at(dictionaryName).printAntonym(word, output);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::translateCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string parameter;
  input >> parameter;
  std::string dictionaryName;
  input >> dictionaryName;
  if (parameter == "sentence")
  {
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
  else if (parameter == "file")
  {
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
}

void nikitov::saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string parameter;
  input >> parameter;
  std::string dictName;
  input >> dictName;
  std::string newFileName;
  input >> newFileName;
  if (parameter == "dictionary")
  {
    std::ofstream fileOutput(newFileName);
    dictOfDicts.at(dictName).printDictionary(fileOutput);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}