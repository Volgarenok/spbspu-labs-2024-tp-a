#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <istream>
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

    void printTranslation(const std::string& word, std::ostream& output) const;
    void printAntonym(const std::string& word, std::ostream& output) const;
    void printDictionary(std::ostream& output) const;

    friend std::istream& operator>>(std::istream& input, Dictionary& dict);

  private:
    std::map< std::string, detail::Word > data_;
  };

  std::istream& operator>>(std::istream& input, Dictionary& dict);
}
#endif