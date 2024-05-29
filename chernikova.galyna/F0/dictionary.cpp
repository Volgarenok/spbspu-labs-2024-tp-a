#include "dictionary.hpp"
#include <algorithm>
#include <functional>

void chernikova::Dictionary::print(std::ostream& output) const
{
  output << DictionaryO{ data_ };
}

int chernikova::Dictionary::print(std::ostream& output, const std::string& word) const
{
  auto iterator = data_.find(word);

  if (iterator == data_.end())
  {
    return 1;
  }

  if (iterator->second.empty())
  {
    return 2;
  }

  output << iterator->first << " : ";
  //printSet(output, iterator->second);
  output << TranslationsO{ iterator->second };
  output << std::endl;

  return 0;
}

bool chernikova::Dictionary::read(std::istream& in)
{
  std::string word;
  while (!in.eof())
  {
    in >> word;

    if (!in)
    {
      return true;
    }

    in >> ExactSymbolI{ ' ' } >> ExactSymbolI{ ':' };

    if (!in)
    {
      return false;
    }

    std::set< std::string > translations = {};

    char delimeter = 0;
    in >> AnySymbolI{ " \n", delimeter };

    std::string translation;
    while (delimeter != '\n')
    {
      in >> translation;

      if (!in)
      {
        return false;
      }

      translations.insert(translation);

      in >> AnySymbolI{ " \n", delimeter };
    }

    if (translations.empty())
    {
      return false;
    }

    data_.insert({ word, translations });
  }
  return true;
}

bool chernikova::Dictionary::insert(const std::string& word, std::string& translation)
{
  auto iterator = data_.find(word);

  if (iterator != data_.end())
  {
    auto iterator2 = iterator->second.find(translation);

    if (iterator2 != iterator->second.end())
      return false;
  }

  data_[word].insert(translation);
  return true;
}

void chernikova::Dictionary::insert(const std::string& word, const std::set< std::string >& translations)
{
  data_.insert({ word, translations });
}

bool chernikova::Dictionary::erase(const std::string& word)
{
  auto iterator = data_.find(word);

  if (iterator == data_.end())
  {
    return false;
  }

  data_.erase(iterator);

  return true;
}

std::set< std::string > chernikova::Dictionary::getTranslations(const std::string& word) const
{
  auto iterator = data_.find(word);

  if (iterator == data_.end())
  {
    return std::set< std::string >();
  }

  return iterator->second;
}

bool chernikova::Dictionary::editWord(const std::string& word, const std::set< std::string >& translations)
{
  auto iterator = data_.find(word);

  if (iterator == data_.end())
  {
    return false;
  }

  iterator->second = translations;

  return true;
}

void chernikova::Dictionary::clear()
{
  data_.clear();
}

size_t chernikova::Dictionary::getSize() const
{
  return data_.size();
}

void chernikova::Dictionary::mergeFrom(Dictionary& other)
{
  std::copy(other.data_.begin(), other.data_.end(), std::inserter(this->data_, this->data_.end()));
  other.clear();
}

chernikova::Dictionary chernikova::Dictionary::intersection(const Dictionary& other) const
{
  Dictionary intersection = {};
  std::copy_if(
    this->data_.begin(),
    this->data_.end(),
    std::inserter(intersection.data_, intersection.data_.end()),
    std::bind(chernikova::Dictionary::isInIntersection, std::placeholders::_1, other.data_));

  return intersection;
}

bool chernikova::Dictionary::isInIntersection(
  const std::pair< std::string, std::set< std::string > >& element,
  const map& elementsSet)
{
  return (elementsSet.find(element.first) != elementsSet.end());
}
