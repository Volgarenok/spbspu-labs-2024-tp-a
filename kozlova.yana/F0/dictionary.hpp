#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>

namespace kozlova
{
  using pair = std::pair< std::string, size_t >;

  class Dictionary
  {
  public:
    Dictionary() = default;
    ~Dictionary() = default;
    Dictionary(const std::map< std::string, size_t >& dictionary);
    explicit Dictionary(const std::string& name);
    Dictionary(const Dictionary& dictionary) = default;
    Dictionary(Dictionary && dictionary) noexcept = default;
    Dictionary& operator=(const Dictionary & dictionary) = default;
    Dictionary& operator=(Dictionary && dictionary) noexcept = default;

    std::string getName() const;
    std::map< std::string, size_t >::const_iterator cbegin() const;
    std::map< std::string, size_t >::iterator begin();
    std::map< std::string, size_t >::const_iterator cend() const;
    std::map< std::string, size_t >::iterator end();
    std::map< std::string, size_t > getDict() const;
    std::map< std::string, size_t >& getDict();
    std::map< std::string, size_t >::const_iterator search(const std::string& word) const;
    void insertWords(std::istream& in);
    void insertPart(std::istream& in, std::string& word1, std::string word2);
    void addWord(const std::string& word, const size_t& number);
    void deleteWord(const std::string& word);
    bool empty() const;
    size_t size() const;
    size_t getOften(const std::string word);

  private:
    std::map<std::string, size_t> dictionary_;
    std::string name_;
  };
}

#endif
