#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <map>
#include <set>
#include <iostream>

namespace novokhatskiy
{
  class Dictionary
  {
  public:
    using val_t = std::pair< std::string, std::set< std::string > >;
    Dictionary() = default;
    ~Dictionary() = default;
    void addValue(Dictionary&& other);
    val_t& getValue(const std::string& name);
    const val_t& getValue(const std::string& name) const;
    std::map< std::string, val_t >& getDict();
    void remove(const std::string& word);
    void find(const std::string& word, std::ostream& out) const;
    size_t size() const noexcept;
    std::map< std::string, val_t > getDict() const;
  private:
    std::map< std::string, val_t > dict_;
  };
  std::istream& operator>>(std::istream& in, Dictionary& dict);
  std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
}

#endif
