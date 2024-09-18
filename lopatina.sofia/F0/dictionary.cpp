#include "dictionary.hpp"

lopatina::Dictionary::Dictionary(const std::map< std::string, size_t > & dict):
  words_(dict)
{}

void lopatina::Dictionary::addWord(const std::string & word, const int & num)
{
  auto iter = words_.find(word);
  if (iter != words_.end())
  {
    (*iter).second += num;
    return;
  }
  words_.insert(std::pair< std::string, size_t >(word, num));
}

void lopatina::Dictionary::deleteWord(const std::string & word)
{
  auto iter = words_.find(word);
  if (iter != words_.end())
  {
    words_.erase(iter);
  }
}

bool lopatina::Dictionary::checkWord(const std::string & word)
{
  if (words_.find(word) != words_.end())
  {
    return true;
  }
  return false;
}

std::map< std::string, size_t > lopatina::Dictionary::getDict() const
{
  return words_;
}

std::map< std::string, size_t > & lopatina::Dictionary::getDict()
{
  return words_;
}

std::istream & lopatina::operator>>(std::istream & in, Dictionary & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Dictionary dict;
  std::string word;
  while (in >> word)
  {
    dict.addWord(word);
  }
  if (in.eof())
  {
    dest = dict;
  }
  return in;
}
