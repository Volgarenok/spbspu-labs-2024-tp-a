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

  std::istream & operator>>(std::istream & input, Dictionary & dict);
  std::ostream & operator<<(std::ostream & output, const Dictionary & dict);
}

#endif
