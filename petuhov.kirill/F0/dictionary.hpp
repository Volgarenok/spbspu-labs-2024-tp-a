#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <set>
#include <string>
#include <iostream>

namespace petuhov
{

  class Dictionary
  {
  public:
    void insert(const std::string &word, const std::string &translation);
    void remove(const std::string &word);
    void translate(const std::string &word) const;
    void merge(const Dictionary &other);
    void combining(const Dictionary &other) const;
    void difference(const Dictionary &other) const;

  private:
    std::map<std::string, std::set<std::string>> dictionary_;
  };

}

#endif
