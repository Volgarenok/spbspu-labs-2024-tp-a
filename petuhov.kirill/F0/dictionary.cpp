#include "dictionary.hpp"

namespace petuhov
{

  void Dictionary::insert(const std::string &word, const std::string &translation)
  {
    dictionary_[word].insert(translation);
  }

  void Dictionary::remove(const std::string &word)
  {
    auto it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      std::cout << "<WORD NOT FOUND>\n";
      return;
    }
    dictionary_.erase(it);
  }

  void Dictionary::translate(const std::string &word) const
  {
    auto it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      std::cout << "<WORD NOT FOUND>\n";
      return;
    }
    for (const auto &translation : it->second)
    {
      std::cout << translation << " ";
    }
    std::cout << "\n";
  }

  void Dictionary::merge(const Dictionary &other)
  {
    for (const auto &entry : other.dictionary_)
    {
      dictionary_[entry.first].insert(entry.second.begin(), entry.second.end());
    }
  }

  void Dictionary::combining(const Dictionary &other) const
  {
    std::set<std::string> combinedWords;
    for (const auto &entry : dictionary_)
    {
      combinedWords.insert(entry.first);
    }
    for (const auto &entry : other.dictionary_)
    {
      combinedWords.insert(entry.first);
    }
    for (const auto &word : combinedWords)
    {
      std::cout << word << " ";
    }
    std::cout << "\n";
  }

  void Dictionary::difference(const Dictionary &other) const
  {
    std::vector<std::string> differences;

    for (const auto &entry : dictionary_)
    {
      const std::string &word = entry.first;
      const std::set<std::string> &translations = entry.second;

      auto it2 = other.dictionary_.find(word);
      if (it2 == other.dictionary_.end())
      {
        differences.push_back(word);
      }
      else
      {
        for (const auto &translation : translations)
        {
          if (it2->second.find(translation) == it2->second.end())
          {
            differences.push_back(word + " " + translation);
          }
        }
      }
    }

    if (differences.empty())
    {
      std::cout << "<EQUAL DICTIONARIES>\n";
    }
    else
    {
      for (const auto &diff : differences)
      {
        std::cout << diff << "\n";
      }
    }
  }

}
