#ifndef DICTIONARYMANAGER_HPP
#define DICTIONARYMANAGER_HPP

#include "dictionary.hpp"
#include <map>
#include <string>

namespace petuhov
{
  using namespace std;

  class DictionaryManager
  {
  public:
    void create(const string &name);
    void deleteDictionary(const string &name);
    void insert(const string &dictName, const string &word, const string &translation);
    void remove(const string &dictName, const string &word);
    void translate(const string &dictName, const string &word) const;
    void merge(const string &dict1, const string &dict2);
    void combining(const string &dict1, const string &dict2) const;
    void difference(const string &dict1, const string &dict2) const;

  private:
    map< string, Dictionary > dictionaries_;
  };
}

#endif
