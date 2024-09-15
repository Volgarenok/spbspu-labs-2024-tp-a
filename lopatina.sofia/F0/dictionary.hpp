#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <string>
#include <map>

namespace lopatina
{
  class Dictionary
  {
  public:
    Dictionary() = default;
    Dictionary(const std::map< std::string, size_t > & dict);
    Dictionary(const Dictionary &) = default;
    ~Dictionary() = default;
    Dictionary & operator=(const Dictionary &) = default;

    void addWord(const std::string & word, const int & num = 1);
    void deleteWord(const std::string & word);
    bool checkWord(const std::string & word);
    std::map< std::string, size_t > getDict() const;
    std::map< std::string, size_t > & getDict();

  private:
    std::map< std::string, size_t > words_;
  };

  std::istream & operator>>(std::istream & in, Dictionary & dest);
}

#endif
