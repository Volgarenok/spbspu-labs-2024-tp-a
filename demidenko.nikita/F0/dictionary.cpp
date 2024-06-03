#include "dictionary.hpp"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>

demidenko::Dictionary::Dictionary():
  tree_()
{}
bool demidenko::Dictionary::addRecord(Record&& record)
{
  if (record.second.empty())
  {
    return false;
  }
  if (tree_.count(record.first))
  {
    if (tree_[record.first] == record.second)
    {
      return false;
    }
    else
    {
      tree_[record.first].insert(record.second.begin(), record.second.end());
    }
  }
  else
  {
    tree_[record.first] = record.second;
  }
  return true;
}
bool demidenko::Dictionary::removeRecord(const Record& record)
{
  if (tree_.count(record.first))
  {
    std::set< std::string > difference;
    auto& target = tree_[record.first];
    std::set_difference(
      target.begin(),
      target.end(),
      record.second.begin(),
      record.second.end(),
      std::inserter(difference, difference.end())
    );
    bool hasCommonTranslations = difference != target;
    target = difference;
    if (tree_[record.first].empty())
    {
      tree_.erase(record.first);
    }
    return hasCommonTranslations;
  }
  return false;
}
bool demidenko::Dictionary::translate(const std::string& word, std::ostream& out) const
{
  try
  {
    auto& translations = tree_.at(word);
    using OutputIterator = std::ostream_iterator< std::string >;
    std::copy(translations.begin(), translations.end(), OutputIterator{ out, "\n" });
    return true;
  }
  catch (...)
  {
    return false;
  }
}
void demidenko::Dictionary::search(const std::string& translation, std::ostream& out) const
{
  for (auto& record : tree_)
  {
    if (record.second.count(translation))
    {
      out << record.first << '\n';
    }
  }
}
void demidenko::Dictionary::prefix(const std::string& prefix, std::ostream& out) const
{
  auto iterator = tree_.lower_bound(prefix);
  while (iterator != tree_.end())
  {
    bool prefixIsShorter = prefix.size() <= iterator->first.size();
    bool prefixIsMatching = prefixIsShorter && std::equal(prefix.begin(), prefix.end(), iterator->first.begin());
    if (prefixIsMatching)
    {
      out << iterator->first << '\n';
    }
    else
    {
      break;
    }
    ++iterator;
  }
}
void demidenko::Dictionary::merge(const Dictionary& other)
{
  if (this == &other)
  {
    return;
  }
  for (auto& record : other.tree_)
  {
    addRecord(Record{ record });
  }
}
void demidenko::Dictionary::exclude(const Dictionary& other)
{
  if (this == &other)
  {
    tree_.clear();
    return;
  }
  for (auto& record : other.tree_)
  {
    removeRecord(record);
  }
}
void demidenko::Dictionary::split(const std::string& word, Dictionary& first, Dictionary& second)
{
  auto point = tree_.lower_bound(word);
  if (this != &first)
  {
    for (auto iterator = tree_.begin(); iterator != point; ++iterator)
    {
      first.addRecord(Record{ *iterator });
    }
  }
  if (this != &second)
  {
    for (auto iterator = point; iterator != tree_.end(); ++iterator)
    {
      second.addRecord(Record{ *iterator });
    }
  }
}
std::istream& demidenko::operator>>(std::istream& in, Dictionary& dictionary)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Dictionary::Record record;
  while (!in.eof())
  {
    readRecord(in, record);
    if (!in.eof() && in.fail())
    {
      return in;
    }
    dictionary.tree_.insert(record);
  }
  in.clear();
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const Dictionary& dictionary)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  for (auto& record : dictionary.tree_)
  {
    printRecord(out, record);
    out << '\n';
  }
  return out;
}
std::istream& demidenko::readRecord(std::istream& in, Dictionary::Record& record)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string line;
  std::getline(in, line);
  Dictionary::Record newRecord;
  auto begin = line.begin();
  auto delimeter = std::find(begin, line.end(), ':');
  if (delimeter == line.end())
  {
    newRecord.first = line;
  }
  else
  {
    newRecord.first = std::string{ begin, delimeter };
    while (delimeter != line.end())
    {
      begin = ++delimeter;
      delimeter = std::find(begin, line.end(), ',');
      if (begin == delimeter)
      {
        in.setstate(std::ios::failbit);
        std::cerr << line;
        return in;
      }
      newRecord.second.insert(std::string{ begin, delimeter });
    }
  }
  record = newRecord;
  return in;
}
std::ostream& demidenko::printRecord(std::ostream& out, const Dictionary::Record& record)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << record.first << ':';
  using OutputIterator = std::ostream_iterator< std::string >;
  if (!record.second.empty())
  {
    std::copy(record.second.begin(), std::prev(record.second.end()), OutputIterator{ out, "," });
    out << *record.second.rbegin();
  }
  return out;
}
