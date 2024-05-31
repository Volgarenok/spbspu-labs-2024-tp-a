#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iosfwd>
#include <map>
#include <string>

namespace erohin
{
  struct Dictionary
  {
    std::map< std::string, size_t > records;
  };

  struct NamedDictionary
  {
    std::pair< std::string, Dictionary > dictionary;
  };

  std::istream & operator>>(std::istream & input, Dictionary & dict);
  std::ostream & operator<<(std::ostream & output, const Dictionary & dict);
  std::istream & operator>>(std::istream & input, NamedDictionary & dict);
  std::ostream & operator<<(std::ostream & output, const NamedDictionary & dict);
  NamedDictionary createNamedDictionary(const std::pair< std::string, Dictionary > & dict);
}

#endif
