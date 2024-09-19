#include "dictionary.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

namespace kozlova
{
  Dictionary::Dictionary(const std::string& name) :
    name_(name)
  {}

  Dictionary::Dictionary(const std::map< std::string, size_t >& dictionary) :
    dictionary_(dictionary)
  {}

  std::string Dictionary::getName() const
  {
    return name_;
  }

  std::map< std::string, size_t >::const_iterator Dictionary::cbegin() const
  {
    return dictionary_.begin();
  }

  std::map< std::string, size_t >::iterator Dictionary::begin()
  {
    return dictionary_.begin();
  }

  std::map< std::string, size_t >::const_iterator Dictionary::cend() const
  {
    return dictionary_.end();
  }

  std::map< std::string, size_t >::iterator Dictionary::end()
  {
    return dictionary_.end();
  }

  std::map< std::string, size_t > Dictionary::getDict() const
  {
    return dictionary_;
  }

  std::map< std::string, size_t >& Dictionary::getDict()
  {
    return dictionary_;
  }

  std::map< std::string, size_t >::const_iterator Dictionary::search(const std::string& word) const
  {
    return dictionary_.find(word);
  }

  void Dictionary::addWord(const std::string& word, const size_t& number)
  {
    auto iterator = dictionary_.find(word);
    if (iterator != dictionary_.end())
    {
      (*iterator).second += number;
      return;
    }
    pair pair = std::make_pair(word, number);
    dictionary_.insert(pair);
    }

  void Dictionary::insertWords(std::istream& in)
  {
    std::string word;
    while (in >> word)
    {
      std::string cleanWord;
      for (size_t i = 0; i < word.length(); ++i)
      {
        char c = word[i];
        if (std::isalpha(c))
        {
          cleanWord += std::tolower(c);
        }
      }
      if (!cleanWord.empty())
      {
        this->addWord(cleanWord, 1);
      }
    }
  }

  void Dictionary::insertPart( std::istream& in, std::string& word1, std::string word2)
  {
    std::string word;
    bool inRange = false;
    while (in >> word)
    {
      std::string cleanWord;
      for (size_t i = 0; i < word.length(); ++i)
      {
        char c = word[i];
        if (std::isalpha(c))
        {
          cleanWord += std::tolower(c);
        }
      }

      if (cleanWord == word1)
      {
        inRange = true;
      }
      if (inRange)
      {
        this->addWord(cleanWord, 1);
      }
      if (cleanWord == word2)
      {
        break;
      }
    }
  }

  void Dictionary::deleteWord(const std::string word)
  {
    auto iterator = dictionary_.find(word);
    if (iterator != dictionary_.end())
    {
      dictionary_.erase(word);
    }
  }
}
