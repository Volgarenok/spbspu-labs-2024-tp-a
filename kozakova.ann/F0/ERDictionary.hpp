#ifndef ERDICTIONARY_HPP
#define ERDICTIONARY_HPP

#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
namespace kozakova
{
  struct ERDictionary
  {
    bool insert(const std::string& word, const std::string& trans);
    const std::set< std::string >* search(const std::string& word) const;
    bool remove(const std::string& word);
    bool removeTrans(const std::string& word, const std::string& trans);
    std::string searchShort(const std::string& word) const;
    std::set< std::string > searchSame(const std::string& word1, const std::string& word2) const;
    bool operator==(const ERDictionary& dict) const;
    void combine(const ERDictionary& dict);

    std::unordered_map< std::string, std::set< std::string > > dictionary;
  };
  std::istream& operator>>(std::istream& in, ERDictionary& dict);
  bool isWord(const std::string& word);
  bool isTrans(const std::string& trans);
  bool isEnglish(const char& c);
  bool isRussian(const char& c);
  bool isShortTrans(const std::string& trans1, const std::string& trans2);
  bool inDict(const ERDictionary& dict, const std::pair< std::string, std::set< std::string > >& el);
  std::unordered_map< std::string, std::set< std::string > > intersect(const ERDictionary& dict1, const ERDictionary& dict2);
  void print(std::ofstream& out, const std::pair< const std::string, kozakova::ERDictionary >& el);
  void printPair(std::ofstream& out, const std::string& nameDict, const std::pair< std::string, std::set< std::string > >& el);
  void printWord(std::ofstream& out, const std::string& nameDict, const std::string& word, const std::string& el);
}

#endif
