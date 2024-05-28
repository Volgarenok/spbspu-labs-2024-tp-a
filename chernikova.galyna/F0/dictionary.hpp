#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>

namespace chernikova
{
  class Dictionary
  {
  public:
    void print(std::ostream& output) const;
    int print(std::ostream& output, const std::string& word) const;
    bool read(std::istream& in);
    bool insert(const std::string& word, std::string& translation);
    void insert(const std::string& word, const std::set< std::string >& translations);
    bool erase(const std::string& word);
    std::set< std::string > getTranslations(const std::string& word) const;
    bool editWord(const std::string& word, const std::set< std::string >& translations);
    void clear();
    size_t getSize() const;
    void mergeFrom(Dictionary& other);
    Dictionary intersection(const Dictionary& other) const;
  private:
    using map = std::unordered_map< std::string, std::set< std::string > >;
    map data_;

    static bool isInIntersection(
      const std::pair< std::string, std::set< std::string > >& element,
      const map& elementsSet);
    static void printSet(std::ostream& output, const std::set < std::string >& set);
  };
}

#endif
