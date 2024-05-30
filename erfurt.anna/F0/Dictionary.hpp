#ifndef RGR_ENG_RUS_DICTIONARY_HPP
#define RGR_ENG_RUS_DICTIONARY_HPP

#include <map>
#include <set>
#include <string>
#include <memory>
#include <ostream>

namespace erfurt
{
  using pair = std::pair< std::string, std::set< std::string > >;

  class Dictionary
  {
  public:
    Dictionary() = default;
    ~Dictionary() = default;
    explicit Dictionary(const std::string & name);
    Dictionary(const Dictionary & dictionary) = default;
    Dictionary(Dictionary && dictionary) noexcept = default;
    Dictionary& operator=(const Dictionary & dictionary) = default;
    Dictionary& operator=(Dictionary && dictionary) noexcept = default;

    std::map< std::string, std::set< std::string > >::const_iterator cbegin() const;
    std::map< std::string, std::set< std::string > >::iterator begin();
    std::map< std::string, std::set< std::string > >::const_iterator cend() const;
    std::map< std::string, std::set< std::string > >::iterator end();
    std::map< std::string, std::set< std::string > >::const_iterator search(const std::string & word) const;
    std::set< std::string > & operator[](const std::string & key);

    void insert(const std::string & word, const std::string & translate);
    void insert(const pair & item);
    std::string getName() const;
    void printTranslate(std::ostream & out, const std::string & word) const;
    bool deleteWord(const std::string & word);

    friend std::istream& operator>>(std::istream & in, Dictionary & dictionary);
  private:
    std::map< std::string, std::set< std::string > > dictionary_;
    std::string name_;
  };
}

#endif
