#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <istream>
#include <map>
#include "word.hpp"

namespace nikitov
{
  class Dictionary
  {
    void addTranslation(const std::string& word, const std::string& translation);
    void addAntonym(const std::string& word, const std::string& antonym);
    void deletePrimaryTranslation(const std::string& word);
    void deleteSecondaryTranslation(const std::string& word);

    std::map< std::string, detail::Word > data_;
  };
}
#endif