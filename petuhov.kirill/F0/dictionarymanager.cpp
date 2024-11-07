#include "dictionarymanager.hpp"
#include <iostream>

using namespace std;

namespace petuhov
{

  void DictionaryManager::create(const string &name)
  {
    if (dictionaries_.find(name) != dictionaries_.end())
    {
      cout << "<ALREADY EXISTS>\n";
      return;
    }
    dictionaries_[name] = Dictionary();
  }

  void DictionaryManager::deleteDictionary(const string &name)
  {
    if (dictionaries_.erase(name) == 0)
    {
      cout << "<DICTIONARY NOT FOUND>\n";
    }
  }

  void DictionaryManager::insert(const string &dictName, const string &word, const string &translation)
  {
    map< string, Dictionary >::iterator it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.insert(word, translation);
  }

  void DictionaryManager::remove(const string &dictName, const string &word)
  {
    map< string, Dictionary >::iterator it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.remove(word);
  }

  void DictionaryManager::translate(const string &dictName, const string &word) const
  {
    map< string, Dictionary >::const_iterator it = dictionaries_.find(dictName);
    if (it == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it->second.translate(word);
  }

  void DictionaryManager::merge(const string &dict1, const string &dict2)
  {
    map< string, Dictionary >::iterator it1 = dictionaries_.find(dict1);
    map< string, Dictionary >::iterator it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.merge(it2->second);
  }

  void DictionaryManager::combining(const string &dict1, const string &dict2) const
  {
    map< string, Dictionary >::const_iterator it1 = dictionaries_.find(dict1);
    map< string, Dictionary >::const_iterator it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.combining(it2->second);
  }

  void DictionaryManager::difference(const string &dict1, const string &dict2) const
  {
    map< string, Dictionary >::const_iterator it1 = dictionaries_.find(dict1);
    map< string, Dictionary >::const_iterator it2 = dictionaries_.find(dict2);
    if (it1 == dictionaries_.end() || it2 == dictionaries_.end())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    it1->second.difference(it2->second);
  }

}
