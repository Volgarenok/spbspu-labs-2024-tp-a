#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace petuhov
{
  using namespace std;

  class Dictionary
  {
  public:
    void create(const string &name);
    void deleteDictionary(const string &name);
    void insert(const string &word, const string &translation);
    void remove(const string &word);
    void translate(const string &word) const;
    void merge(const Dictionary &other);
    void combining(const Dictionary &other) const;
    void difference(const Dictionary &other) const;

  private:
    map< string, set< string > > dictionary_;
  };
}

#endif
