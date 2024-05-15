#ifndef HASH_HPP
#define HASH_HPP

#include <list>
#include <string>
#include <iostream>

namespace zaparin
{
  class HashTable
  {
  private:

    size_t defaultSize_ = 10;
    float rehashSize_ = 0.5;

    struct Node
    {
      size_t numOfWords_;
      std::string word_;
      Node() : numOfWords_(0), word_("") {}
      Node (const std::string& word, size_t numOfWords = 1) : numOfWords_(numOfWords), word_(word) {}
    };

    std::list< Node >* table_;
    size_t size_;
    size_t maxSize_;
    size_t allWords_;

    size_t hashFunc(const std::string& word);
    bool insert(std::string&& word, size_t numOfWords = 1);

  public:
    HashTable();
    HashTable(const size_t nol);
    HashTable(const HashTable& table);
    HashTable(HashTable&& table);
    ~HashTable();

    HashTable& operator=(const HashTable& table);
    HashTable& operator=(HashTable&& table);

    bool insert(const std::string& word, size_t numOfWords = 1);
    bool removeWord(const std::string& word);
    bool deleteWord(const std::string& word);
    double getWordRate(const std::string& word);
    std::string getHighestRateWord();
    std::string getLowestRateWord();
    bool getThreeHighestRateWords();
    bool getWordsWithRate(double leftBorder, double rightBorder);
    bool mergeDicts(const HashTable& dict1, const HashTable& dict2);
    bool intersectDicts(HashTable& dict);
    bool print(std::ostream& out);
  };
}

#endif