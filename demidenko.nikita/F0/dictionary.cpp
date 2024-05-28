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
void demidenko::Dictionary::translate(const std::string& word, std::ostream& out) const
{
  auto& translations = tree_.at(word);
  using OutputIterator = std::ostream_iterator< std::string >;
  std::copy(translations.begin(), translations.end(), OutputIterator{ out, "\n" });
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
  for (auto& record : other.tree_)
  {
    addRecord(Record{ record });
  }
}
void demidenko::Dictionary::exclude(const Dictionary& other)
{
  for (auto& record : other.tree_)
  {
    removeRecord(record);
  }
}
void demidenko::Dictionary::split(const std::string& word, Dictionary& first, Dictionary& second)
{
  auto point = tree_.lower_bound(word);
  for (auto iterator = tree_.begin(); iterator != point; ++iterator)
  {
    first.addRecord(Record{ *iterator });
  }
  for (auto iterator = point; iterator != tree_.end(); ++iterator)
  {
    second.addRecord(Record{ *iterator });
  }
}
std::istream& demidenko::operator>>(std::istream& in, Dictionary& dictionary)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    std::cerr << in.eof() << in.fail() << '\n';
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
namespace demidenko
{
  std::istream& readDelimited(std::istream& in, std::string& word, char delimeter)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    word.clear();
    char current = in.get();
    while (in.good() && !(std::isspace(current) || current == delimeter))
    {
      word.push_back(current);
      current = in.get();
    }
    if (std::isspace(current))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
std::istream& demidenko::readRecord(std::istream& in, Dictionary::Record& record)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Dictionary::Record newRecord;
  readDelimited(in, newRecord.first, ':');
  if (in.fail())
  {
    in.clear();
    record = newRecord;
    return in;
  }
  std::string translation;
  while (in.good())
  {
    readDelimited(in, translation, ',');
    newRecord.second.insert(translation);
    if (in.fail())
    {
      in.clear();
      record = newRecord;
      return in;
    }
  }
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
