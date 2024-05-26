#include "commands.hpp"
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <numeric>

using mapDict = std::map< std::string, kornienko::Dictionary >;
void kornienko::createDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string newName;
  in >> newName;
  auto iter = dictionaries.find(newName);
  if (iter != dictionaries.end())
  {
    throw std::logic_error("ALREADY EXIST\n");
  }
  dictionaries[newName];
}

void kornienko::deleteDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  auto iter = dictionaries.find(name);
  if (iter != dictionaries.end())
  {
     dictionaries.erase(name);
  }
  else
  {
     throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}

bool isEnglishWord(const std::string & word)
{
  for (const auto & letter : word)
  {
    if (letter < 'A' || letter > 'z')
    {
      return false;
    }
  }
  return true;
}

bool isRussianWord(const std::string & word)
{
  for (const auto & letter : word)
  {
    if (letter < 'A' || letter > 'z')
    {
      return false;
    }
  }
  return true;
}

void kornienko::addWord(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (!isEnglishWord(word))
  {
    throw std::logic_error("INCORRECT WORD\n");
  }
  auto iter1 = dictionaries.find(dictName);
  if (iter1 != dictionaries.end())
  {
    auto iter2 = dictionaries[dictName].dictionary_.find(word);
    if (iter2 != dictionaries[dictName].dictionary_.end())
    {
      throw std::logic_error("WORD ALREADY EXISTS\n");
    }
    else
    {
      dictionaries[dictName].dictionary_[word];
    }
  }
  else
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}

void kornienko::deleteWord(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  auto iter1 = dictionaries.find(dictName);
  if (iter1 != dictionaries.end())
  {
    auto iter2 = dictionaries[dictName].dictionary_.find(word);
    if (iter2 != dictionaries[dictName].dictionary_.end())
    {
      dictionaries[dictName].dictionary_.erase(word);
    }
    else
    {
      throw std::logic_error("WORD DOESN’T EXIST\n");
    }
  }
  else
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}

void kornienko::addTranslation(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  setlocale(LC_ALL, "RU");
  std::string dictName;
  std::string word;
  std::string translation;
  in >> dictName >> word >> translation;
  if (!isEnglishWord(word))
  {
    throw std::logic_error("INCORRECT WORD\n");
  }
  if (!isRussianWord(translation))
  {
    throw std::logic_error("INCORRECT TRANSLATION\n");
  }
  auto iter1 = dictionaries.find(dictName);
  if (iter1 != dictionaries.end())
  {
    auto iter2 = dictionaries[dictName].dictionary_.find(word);
    if (iter2 != dictionaries[dictName].dictionary_.end())
    {
      dictionaries[dictName].dictionary_[word].push_back(translation);
      sort(dictionaries[dictName].dictionary_[word].begin(), dictionaries[dictName].dictionary_[word].end());
    }
    else
    {
      throw std::logic_error("INCORRECT WORD\n");
    }
  }
  else
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}

void kornienko::output(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  auto iter = dictionaries.find(name);
  if (iter != dictionaries.end())
  {
     out << name << " words:\n";
     for (const auto& words : dictionaries[name].dictionary_)
     {
       out << words.first << ": ";
       for (const auto& trans : words.second)
       {
         out << trans << " ";
       }
       out << "\n";
     }
  }
  else
  {
     throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}
