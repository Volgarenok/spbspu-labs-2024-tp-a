#ifndef _DICTIONARY_HPP
#define _DICTIONARY_HPP

#include <string>
#include <map>

class Dictionary
{
public:
  Dictionary() = default;
  ~Dictionary() = default;
private:
  std::map< std::string, std::string > map;
};

#endif
