#include "dictionary.hpp"
#include <stdexcept>

using val_t = std::pair< std::string, std::set< std::string > >;

std::istream& novokhatskiy::operator>>(std::istream& in, Dictionary& dict)
{
  std::string word = {};
  std::string translation = {};
  in >> word >> translation;
  std::string example = {};
  std::string tmp = {};
  std::getline(in, example, '\n');
  std::pair< std::string, std::set< std::string > > pair;
  pair.first = translation;
  for (size_t i = 0; example[i] != '\0'; i++)
  {
    tmp += example[i];
    if (example[i] == '.' || example[i] == '!' || example[i] == '?')
    {
      pair.second.insert(tmp);
      tmp = {};
    }
  }
  dict.getDict()[word] = pair;
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Dictionary& dict)
{
  if (dict.getDict().empty())
  {
    throw std::logic_error("Empty dictionary");
  }
  for (auto i = dict.getDict().cbegin(); i != dict.getDict().cend(); i++)
  {
    out << i->first << ' ' << i->second.first;
    for (auto j = i->second.second.cbegin(); j != i->second.second.cend(); j++)
    {
      out << *j;
    }
    out << '\n';
  }
  return out;
}

void novokhatskiy::Dictionary::addValue(Dictionary&& other)
{
  dict_.insert(*other.getDict().cbegin());
}

val_t& novokhatskiy::Dictionary::getValue(const std::string& name)
{
  return dict_.find(name)->second;
}

const val_t& novokhatskiy::Dictionary::getValue(const std::string& name) const
{
  return dict_.find(name)->second;
}

std::map<std::string, val_t>& novokhatskiy::Dictionary::getDict()
{
  return dict_;
}

void novokhatskiy::Dictionary::remove(const std::string& word)
{
  auto tmp = dict_.find(word);
  if (tmp == dict_.cend())
  {
    throw std::logic_error("This word doesn't exist");
  }
  dict_.erase(tmp);
}

void novokhatskiy::Dictionary::find(const std::string& word, std::ostream& out) const
{
  auto tmp = dict_.find(word);
  if (tmp == dict_.cend())
  {
    throw std::logic_error("The word doesn't exist in the dictionary");
  }
  out << tmp->second.first;
  for (auto i = tmp->second.second.cbegin(); i != tmp->second.second.cend(); i++)
  {
    out << *i;
  }
  out << '\n';
}

size_t novokhatskiy::Dictionary::size() const noexcept
{
  return dict_.size();
}

std::map<std::string, val_t> novokhatskiy::Dictionary::getDict() const
{
  return dict_;
}
