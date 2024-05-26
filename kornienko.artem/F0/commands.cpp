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

void kornienko::merge(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  auto iterNew = dictionaries.find(newName);
  auto iter1 = dictionaries.find(name1);
  auto iter2 = dictionaries.find(name2);
  if (iterNew != dictionaries.end())
  {
    throw std::logic_error("ALREADY EXIST\n");
  }
  if (iter1 == dictionaries.end() || iter2 == dictionaries.end())
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() && itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict1).first] = (*itDict1).second;
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict2).first] = (*itDict2).second;
      ++itDict2;
    }
    else
    {
      auto beg1 = dictionaries[newName].dictionary_[(*itDict1).first].begin();
      dictionaries[newName].dictionary_[(*itDict1).first].insert(beg1, (*itDict1).second.begin(), (*itDict1).second.end());
      auto beg2 = dictionaries[newName].dictionary_[(*itDict2).first].begin();
      dictionaries[newName].dictionary_[(*itDict1).first].insert(beg2, (*itDict2).second.begin(), (*itDict2).second.end());
      std::sort(dictionaries[newName].dictionary_[(*itDict1).first].begin(), dictionaries[newName].dictionary_[(*itDict1).first].end());
      ++itDict1;
      ++itDict2;
    }
  }
  if (itDict1 != dictionaries[name1].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict1, dictionaries[name1].dictionary_.end());
  }
  else if (itDict2 != dictionaries[name2].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict2, dictionaries[name2].dictionary_.end());
  }
}

void kornienko::intersect(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  auto iterNew = dictionaries.find(newName);
  auto iter1 = dictionaries.find(name1);
  auto iter2 = dictionaries.find(name2);
  if (iterNew != dictionaries.end())
  {
    throw std::logic_error("ALREADY EXIST\n");
  }
  if (iter1 == dictionaries.end() || iter2 == dictionaries.end())
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() && itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      ++itDict2;
    }
    else
    {
      auto beg1 = dictionaries[newName].dictionary_[(*itDict1).first].begin();
      dictionaries[newName].dictionary_[(*itDict1).first].insert(beg1, (*itDict1).second.begin(), (*itDict1).second.end());
      auto beg2 = dictionaries[newName].dictionary_[(*itDict2).first].begin();
      dictionaries[newName].dictionary_[(*itDict1).first].insert(beg2, (*itDict2).second.begin(), (*itDict2).second.end());
      std::sort(dictionaries[newName].dictionary_[(*itDict1).first].begin(), dictionaries[newName].dictionary_[(*itDict1).first].end());
      ++itDict1;
      ++itDict2;
    }
  }
}

void kornienko::difference(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  auto iterNew = dictionaries.find(newName);
  auto iter1 = dictionaries.find(name1);
  auto iter2 = dictionaries.find(name2);
  if (iterNew != dictionaries.end())
  {
    throw std::logic_error("ALREADY EXIST\n");
  }
  if (iter1 == dictionaries.end() || iter2 == dictionaries.end())
  {
    throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() && itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict1).first] = (*itDict1).second;
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict2).first] = (*itDict2).second;
      ++itDict2;
    }
    else
    {
      ++itDict1;
      ++itDict2;
    }
  }
  if (itDict1 != dictionaries[name1].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict1, dictionaries[name1].dictionary_.end());
  }
  else if (itDict2 != dictionaries[name2].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict2, dictionaries[name2].dictionary_.end());
  }
}
