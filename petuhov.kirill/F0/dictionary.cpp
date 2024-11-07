#include "dictionary.hpp"

namespace petuhov
{

  void Dictionary::create(const string &name)
  {
    if (!dictionary_.empty())
    {
      cout << "<ALREADY EXISTS>\n";
      return;
    }
  }

  void Dictionary::deleteDictionary(const string &name)
  {
    if (dictionary_.empty())
    {
      cout << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    dictionary_.clear();
  }

  void Dictionary::insert(const string &word, const string &translation)
  {
    if (dictionary_.find(word) != dictionary_.end() && dictionary_[word].find(translation) != dictionary_[word].end())
    {
      cout << "<ALREADY EXISTS>\n";
      return;
    }
    dictionary_[word].insert(translation);
  }

  void Dictionary::remove(const string &word)
  {
    auto it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      cout << "<WORD NOT FOUND>\n";
      return;
    }
    dictionary_.erase(it);
  }

  void Dictionary::translate(const string &word) const
  {
    auto it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      cout << "<WORD NOT FOUND>\n";
      return;
    }
    for (const auto &translation : it->second)
    {
      cout << translation << " ";
    }
    cout << "\n";
  }

  void Dictionary::merge(const Dictionary &other)
  {
    for (const auto &[word, translations] : other.dictionary_)
    {
      dictionary_[word].insert(translations.begin(), translations.end());
    }
  }

  void Dictionary::combining(const Dictionary &other) const
  {
    set<string> combinedWords;
    for (const auto &[word, _] : dictionary_)
    {
      combinedWords.insert(word);
    }
    for (const auto &[word, _] : other.dictionary_)
    {
      combinedWords.insert(word);
    }
    for (const auto &word : combinedWords)
    {
      cout << word << " ";
    }
    cout << "\n";
  }

  void Dictionary::difference(const Dictionary &other) const
  {
    vector<string> differences;

    for (const auto &[word, translations] : dictionary_)
    {
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
      cout << "<EQUAL DICTIONARIES>\n";
    }
    else
    {
      for (const auto &diff : differences)
      {
        cout << diff << "\n";
      }
    }
  }

}
