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

void kornienko::addWord(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string dictName;
  in >> dictName;
  std::string word;
  in >> word;
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
  in >> dictName;
  std::string word;
  in >> word;
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
