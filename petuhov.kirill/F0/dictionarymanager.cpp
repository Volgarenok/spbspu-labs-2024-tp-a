#include "dictionarymanager.hpp"
#include <iostream>

namespace petuhov
{

  void DictionaryManager::create(const std::string &name)
  {
    if (dictionaries_.find(name) != dictionaries_.end())
    {
      std::cout << "<ALREADY EXISTS>\n";
      return;
    }
    dictionaries_[name] = Dictionary();
  }

  void DictionaryManager::deleteDictionary(const std::string &name)
  {
    if (dictionaries_.erase(name) == 0)
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
    }
  }

  void DictionaryManager::insert(const std::string &dictName, const std::string &word, const std::string &translation)
  {
    auto it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.insert(word, translation);
  }

  void DictionaryManager::remove(const std::string &dictName, const std::string &word)
  {
    auto it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.remove(word);
  }

  void DictionaryManager::translate(const std::string &dictName, const std::string &word) const
  {
    auto it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.translate(word);
  }

  void DictionaryManager::merge(const std::string &dict1, const std::string &dict2)
  {
    auto it1 = dictionaries_.find(dict1);
    auto it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.merge(it2->second);
  }

  void DictionaryManager::combining(const std::string &dict1, const std::string &dict2) const
  {
    auto it1 = dictionaries_.find(dict1);
    auto it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.combining(it2->second);
  }

  void DictionaryManager::difference(const std::string &dict1, const std::string &dict2) const
  {
    auto it1 = dictionaries_.find(dict1);
    auto it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      std::cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.difference(it2->second);
  }

}
