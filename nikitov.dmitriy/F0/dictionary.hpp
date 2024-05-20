#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include "word.hpp"

namespace nikitov
{
  class Dictionary
  {
    void addWord(const std::string& word, const std::string& translation, const std::string& antonym);
    void deleteWord(const std::string& word);
    void editWord(const std::string& word, const std::string& translation, const std::string& antonym);

    std::map< std::string, detail::Word > data_;
  };
}
#endif