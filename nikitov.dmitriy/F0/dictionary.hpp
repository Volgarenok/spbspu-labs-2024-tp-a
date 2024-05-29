#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <map>
#include "word.hpp"

namespace nikitov
{
  class Dictionary
  {
  public:
    Dictionary() = default;
    ~Dictionary() = default;

    void addTranslation(const std::string& word, const std::string& translation);
    void editPrimaryTranslation(const std::string& word, const std::string& translation);
    void editSecondaryTranslation(const std::string& word, const std::string& translation);
    void deletePrimaryTranslation(const std::string& word);
    void deleteSecondaryTranslation(const std::string& word);

    void addAntonym(const std::string& word, const std::string& antonym);
    void deleteAntonym(const std::string& word);

    std::string findWord(const std::string& word) const;
    std::string findAntonym(const std::string& word) const;
    std::string findTranslation(const std::string& word) const;

    friend std::istream& operator>>(std::istream& input, Dictionary& dict);
    friend std::ostream& operator<<(std::ostream& output, const Dictionary& dict);
    friend void mergeCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);

  private:
    std::map< std::string, detail::Word > data_;
  };

  std::istream& operator>>(std::istream& input, Dictionary& dict);
  std::ostream& operator<<(std::ostream& output, const Dictionary& dict);
}
#endif
