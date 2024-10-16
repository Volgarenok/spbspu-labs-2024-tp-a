#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <set>
#include <unordered_map>

namespace ayupov
{
  struct ARDictionary
  {
    bool insert(const std::string&, const std::string&);
    bool remove(const std::string&);
    bool removeTranlation(const std::string&, const std::string&);
    const std::set<std::string>* search(const std::string& word) const;
    bool operator==(const ARDictionary&);
    std::unordered_map< std::string, std::set< std::string > > dictionary;
  };
  std::istream& operator>>(std::istream&, ARDictionary&);
  bool isWord(const std::string& word);
    bool isRussian(const char&);
  bool isTranslation(const std::string& translation);
}
#endif
