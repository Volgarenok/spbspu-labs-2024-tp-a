#include "dictionary.hpp"

namespace grechishnikov
{

  Dictionary::Dictionary(std::string name):
    name_(name)
  {}

  std::string Dictionary::at(const std::string& string)
  {
    return this->find(string)->second.translation_;
  }

  void Dictionary::add(const std::string& word, const std::string& translation)
  {
    using namespace detail;
    Node tempRu(translation);
    Node tempEnd(word);
    ruToEng_[word] = tempRu;
    engToRu_[translation] = tempEnd;
    ruToEng_.find(word)->second.where_ = engToRu_.find(translation);
    engToRu_.find(translation)->second.where_ = ruToEng_.find(word);
  }

  void Dictionary::erase(const std::string& key)
  {
    auto dict = findDict(key);
    auto del = dict.first->find(key)->second.where_;
    dict.first->erase(key);
    dict.second->erase(del);
  }

  std::map< std::string, detail::Node >::iterator Dictionary::find(const std::string& key)
  {
    if (ruToEng_.find(key) != ruToEng_.end())
    {
      return ruToEng_.find(key);
    }
    if (engToRu_.find(key) != engToRu_.end())
    {
      return engToRu_.find(key);
    }
    else
    {
      throw std::logic_error("Element was not found");
    }
  }

  std::pair < std::map< std::string, detail::Node >*, std::map< std::string, detail::Node >* > Dictionary::findDict(const std::string& key)
  {
    if (ruToEng_.find(key) != ruToEng_.end())
    {
      return { &ruToEng_, &engToRu_ };
    }
    if (engToRu_.find(key) != engToRu_.end())
    {
      return { &engToRu_, &ruToEng_ };
    }
    else
    {
      throw std::logic_error("Dictionary was not found");
    }
  }
}
