#include "dictionary.hpp"
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

namespace petuhov
{

  void Dictionary::insert(const string &word, const string &translation)
  {
    dictionary_[word].insert(translation);
  }

  void Dictionary::remove(const string &word)
  {
    map< string, set< string > >::iterator it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      cout << "<WORD NOT FOUND>\n";
      return;
    }
    dictionary_.erase(it);
  }

  void Dictionary::translate(const string &word) const
  {
    map< string, set< string > >::const_iterator it = dictionary_.find(word);
    if (it == dictionary_.end())
    {
      cout << "<WORD NOT FOUND>\n";
      return;
    }
    for (set< string >::const_iterator translation = it->second.begin(); translation != it->second.end(); ++translation)
    {
      cout << *translation << " ";
    }
    cout << "\n";
  }

  void Dictionary::merge(const Dictionary &other)
  {
    for (map< string, set< string > >::const_iterator entry = other.dictionary_.begin(); entry != other.dictionary_.end(); ++entry)
    {
      dictionary_[entry->first].insert(entry->second.begin(), entry->second.end());
    }
  }

  void Dictionary::combining(const Dictionary &other) const
  {
    set< string > combinedWords;
    for (map< string, set< string > >::const_iterator entry = dictionary_.begin(); entry != dictionary_.end(); ++entry)
    {
      combinedWords.insert(entry->first);
    }
    for (map< string, set< string > >::const_iterator entry = other.dictionary_.begin(); entry != other.dictionary_.end(); ++entry)
    {
      combinedWords.insert(entry->first);
    }
    for (set< string >::const_iterator word = combinedWords.begin(); word != combinedWords.end(); ++word)
    {
      cout << *word << " ";
    }
    cout << "\n";
  }

  void Dictionary::difference(const Dictionary &other) const
  {
    vector< string > differences;

    for (map< string, set< string > >::const_iterator entry = dictionary_.begin(); entry != dictionary_.end(); ++entry)
    {
      const string &word = entry->first;
      const set< string > &translations = entry->second;

      map< string, set< string > >::const_iterator it2 = other.dictionary_.find(word);
      if (it2 == other.dictionary_.end())
      {
        differences.push_back(word);
      }
      else
      {
        for (set< string >::const_iterator translation = translations.begin(); translation != translations.end(); ++translation)
        {
          if (it2->second.find(*translation) == it2->second.end())
          {
            differences.push_back(word + " " + *translation);
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
      for (vector< string >::const_iterator diff = differences.begin(); diff != differences.end(); ++diff)
      {
        cout << *diff << "\n";
      }
    }
  }

}
