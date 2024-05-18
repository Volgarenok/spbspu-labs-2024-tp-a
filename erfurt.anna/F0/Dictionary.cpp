#include "Dictionary.hpp"
#include <iostream>
#include <algorithm>
#include "Utilites.hpp"

namespace erfurt
{
  Dictionary::Dictionary(const std::string & name) :
    name_(name)
  {}

  Dictionary & Dictionary::operator=(Dictionary && dictionary) noexcept
  {
    name_ = std::move(dictionary.name_);
    dictionary_ = std::move(dictionary.dictionary_);
    return *this;
  }

  std::istream & operator>>(std::istream & in, Dictionary & dictionary)
  {
    setlocale(LC_ALL, "RU");
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    std::string name;
    std::getline(in, name, '\n');
    dictionary.name_ = name;
    std::set< std::string > set;
    while (!in.eof())
    {
      std::string newLine;
      std::getline(in, newLine, '\n');
      std::string word = oneWord(newLine);
      if (word.empty() || !isEng(word) || word == "END")
      {
        return in;
      }
      while (!newLine.empty())
      {
        std::string translate = oneWord(newLine);
        if (isRus(translate))
        {
          set.insert(translate);
        }
      }
      std::shared_ptr<std::set<std::string>> ptr = std::make_shared<std::set<std::string>>(set);
      pair pair = std::make_pair(word, ptr);
      dictionary.insert(pair);
      set.clear();
    }
    return in;
  }

  std::string Dictionary::getName() const
  {
    return name_;
  }

  std::map<std::string, std::shared_ptr<std::set<std::string>>>::const_iterator Dictionary::begin() const
  {
    return dictionary_.begin();
  }

  std::map<std::string, std::shared_ptr<std::set<std::string>>>::iterator Dictionary::begin()
  {
    return dictionary_.begin();
  }

  std::map<std::string, std::shared_ptr<std::set<std::string>>>::const_iterator Dictionary::end() const
  {
    return dictionary_.end();
  }

  std::map<std::string, std::shared_ptr<std::set<std::string>>>::iterator Dictionary::end()
  {
    return dictionary_.end();
  }

  std::map<std::string, std::shared_ptr<std::set<std::string>>>::const_iterator Dictionary::search(const std::string& word) const
  {
    return dictionary_.find(word);
  }

  void Dictionary::insert(const std::string & word, const std::string & translate)
  {
    if (!isEng(word) || !isRus(translate))
    {
      throw std::logic_error("INVALID ARGUMENT");
    }
    auto iterator = dictionary_.find(word);
    if (iterator != dictionary_.end())
    {
      iterator->second->insert(translate);
    }
    else
    {
      std::set<std::string> set;
      std::shared_ptr<std::set<std::string>> ptr = std::make_shared<std::set<std::string>>(set);
      ptr->insert(translate);
      pair pair = std::make_pair(word, ptr);
      dictionary_.insert(pair);
    }
  }

  void Dictionary::insert(const pair & item)
  {
    for (const auto & item1 : *item.second)
    {
      this->insert(item.first, item1);
    }
  }

  void Dictionary::printTranslate(std::ostream & out, const std::string & word) const
  {
    auto iterator = dictionary_.find(word);
    if (iterator != dictionary_.end())
    {
      using output_it_t = std::ostream_iterator<std::string>;
      std::copy(
        iterator->second->begin(),
        iterator->second->end(),
        output_it_t{ std::cout, " " }
      );
      out << '\n';
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  bool Dictionary::deleteWord(const std::string & word)
  {
    auto iterator = dictionary_.find(word);
    if (iterator != dictionary_.end())
    {
      dictionary_.erase(word);
      return true;
    }
    return false;
  }
}
