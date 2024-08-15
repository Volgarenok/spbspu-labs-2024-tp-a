#ifndef DICTIONARY_IO_HPP
#define DICTIONARY_IO_HPP

#include <set>
#include <string>
#include <utility>
#include <unordered_map>
#include <delimiter.hpp>

namespace chernikova
{
  struct TranslationsO
  {
    const std::set< std::string >& set;
  };

  struct DictionaryLineO
  {
    const std::pair< std::string, std::set< std::string > >& pair;
  };

  struct DictionaryO
  {
    const std::unordered_map< std::string, std::set< std::string > >& hashTable;
  };

  DictionaryLineO toDictionaryLineO(const std::pair< std::string, std::set< std::string > >& pair);

  std::ostream& operator<<(std::ostream& output, TranslationsO&& obj);
  std::ostream& operator<<(std::ostream& output, DictionaryLineO&& obj);
  std::ostream& operator<<(std::ostream& output, const DictionaryLineO& obj);
  std::ostream& operator<<(std::ostream& output, DictionaryO&& obj);
}

#endif
