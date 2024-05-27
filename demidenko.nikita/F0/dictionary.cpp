#include "dictionary.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <delimeter.hpp>

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
    bool hasCommonWords = false;
    for (auto& translation : record.second)
    {
      if (tree_.count(translation))
      {
        hasCommonWords = true;
        break;
      }
    }
    if (hasCommonWords)
    {
      tree_[record.first].erase(record.second.begin(), record.second.end());
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
  return true;
}
void demidenko::Dictionary::translate(const std::string& word, std::ostream& out) const
{
  using OutputIterator = std::ostream_iterator< std::string >;
  auto& translations = tree_.at(word);
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
    return in;
  }
  Dictionary::Record record;
  while (!in.eof())
  {
    in >> record;
    dictionary.tree_.insert(record);
  }
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
    out << record << '\n';
  }
  return out;
}
std::istream& demidenko::operator>>(std::istream& in, Dictionary::Record& record)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = demidenko::DelimeterI;
  in >> record.first;
  char colon = in.get();
  switch (colon)
  {
  case '\n':
    record.second.clear();
    return in;
  case ':':
  {
    std::string translation;
    while (in.good())
    {
      std::getline(in, translation, ',');
      record.second.insert(std::move(translation));
    }
    in.clear();
    in >> del{ "\n" };
    return in;
  }
  default:
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const Dictionary::Record& record)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << record.first;
  using OutputIterator = std::ostream_iterator< std::string >;
  std::copy(record.second.begin(), record.second.end(), OutputIterator{ out, "," });
  out << '\n';
  return out;
}
