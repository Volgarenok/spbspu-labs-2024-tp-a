#include "dictionary.hpp"
#include <Delimiter.hpp>

void chernikova::Dictionary::print(std::ostream& output) const
{
  if (data_.empty())
  {
    std::cout << "-" << std::endl;
  }
  else
    for (auto elem : data_)
    {
      output << elem.first << " : ";
      printSet(output, elem.second);
      output << std::endl;
    }
}

void chernikova::Dictionary::print(std::ostream& output, const std::string& word) const
{
  auto iterator = data_.find(word);
  output << iterator->first << " : ";
  printSet(output, iterator->second);
  output << std::endl;
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

    in >> PunctuationI{ ' ' } >> PunctuationI{ ':' };

    if (!in)
    {
      return false;
    }

    std::set< std::string > translations = {};

    while (in.peek() != '\n')
    {
      in >> PunctuationI{ ' ' };

      if (!in)
      {
        return false;
      }

      std::string translation;

      in >> translation;

      if (!in)
      {
        return false;
      }

      translations.insert(translation);
    }
    in >> PunctuationI{ '\n' };

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

void chernikova::Dictionary::printSet(std::ostream& output, const std::set < std::string >& set) {
  if (set.begin() != set.end())
  {
    auto last = set.end();
    --last;

    for (auto it = set.begin(); it != last; ++it)
    {
      output << *it << " ";
    }
    output << *last;
  }
}
