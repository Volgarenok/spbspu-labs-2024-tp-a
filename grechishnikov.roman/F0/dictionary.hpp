#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <map>
#include <stdexcept>
#include "node.hpp"

namespace grechishnikov
{
  class Dictionary
  {
  public:
    std::string name_ ;

    Dictionary(std::string);

    std::string at(const std::string& string);
    void add(const std::string& word, const std::string& translation);
    void erase(const std::string& key);
    std::map< std::string, detail::Node >::iterator find(const std::string& key);
    std::pair < std::map< std::string, detail::Node >*, std::map< std::string, detail::Node >* > findDict(const std::string& key);
  private:
    std::map< std::string, detail::Node > ruToEng_;
    std::map< std::string, detail::Node > engToRu_;
  };
}

#endif
