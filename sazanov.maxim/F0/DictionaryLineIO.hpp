#ifndef DICTIONARY_LINE_IO_HPP
#define DICTIONARY_LINE_IO_HPP

#include <string>

namespace sazanov
{
  struct DictionaryLineI
  {
    std::pair< std::string, size_t > pair;
  };
  std::istream& operator>>(std::istream& in, DictionaryLineI& line);

  struct DictionaryLineO
  {
    const std::pair< std::string, size_t >& pair;
  };
  std::ostream& operator<<(std::ostream& out, const DictionaryLineO& line);
}

#endif
