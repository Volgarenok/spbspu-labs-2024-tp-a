#include "CrossRefs.hpp"

#include <unordered_map>
#include <iterator>
#include <string>
#include <algorithm>
#include  <functional>

std::unordered_map<std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::begin()
{
  return table_.begin();
}
std::unordered_map< std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::end()
{
  return table_.end();
}
std::unordered_map<std::string, std::list< size_t > >::const_iterator stepanchenko::CrossRefs::search(const std::string& word) const
{
  return table_.find(word);
}

bool stepanchenko::CrossRefs::operator==(const CrossRefs& cr) const
{
  return table_ == cr.table_;
}

bool stepanchenko::CrossRefs::operator<(const CrossRefs& cr) const
{
  return table_.bucket_count() < cr.table_.bucket_count();
}

namespace stepanchenko
{
  std::istream& operator>>(std::istream& in, CrossRefs& cr)
  {
    std::string name;
    std::getline(in, name);
    cr.name_ = name;
    std::string line;
    size_t lineNumber = 1;
    while (std::getline(in, line))
    {
      if (line == "------------End of table------------")
      {
        return in;
      }
      cr.lines_.push_back({ lineNumber, line });
      std::istringstream stream(line);
      std::string word;

      std::for_each(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), [&](const std::string& word) {
        std::string lowerWord;
        std::copy_if(word.begin(), word.end(), std::back_inserter(lowerWord), isalpha);
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
        cr.insert(lowerWord, lineNumber);
      });
      ++lineNumber;
    }

    if (line != "------------End of table------------")
    {
      throw std::logic_error("<INVALID COMMAND>");
    }

    return in;
  }
}

void stepanchenko::CrossRefs::createTable(const std::string& tableName, const std::string& fname)
{
  name_ = tableName;
  std::ifstream file;
  file.open(fname);
  std::string line;
  size_t lineNumber = 1;
  while (std::getline(file, line))
  {
    lines_.push_back({ lineNumber, line });
    std::istringstream stream(line);
    std::string word;

    std::for_each(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), [&](const std::string& word) {
      std::string lowerWord;
      std::copy_if(word.begin(), word.end(), std::back_inserter(lowerWord), isalpha);
      std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
      insert(lowerWord, lineNumber);
    });
    ++lineNumber;
  }
}

void stepanchenko::CrossRefs::append(const std::string& fname)
{
  std::ifstream file;
  file.open(fname);
  std::string line;
  size_t lineNumber = lines_.size();
  while (std::getline(file, line))
  {
    lines_.push_back({ lineNumber, line });
    std::istringstream stream(line);
    std::string word;

    std::for_each(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), [&](const std::string& word) {
      std::string lowerWord;
      std::copy_if(word.begin(), word.end(), std::back_inserter(lowerWord), isalpha);
      std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
      insert(lowerWord, lineNumber);
    });
    ++lineNumber;
  }
}

void stepanchenko::CrossRefs::insert(const std::pair < std::string, std::list< size_t > > bucket)
{
  table_.insert(bucket);
}

void stepanchenko::CrossRefs::print(std::ostream& out)
{
  for (const auto& iter : lines_)
  {
    out << iter.first << ' ' << iter.second << '\n';
  }
}

const std::string stepanchenko::CrossRefs::getName() const
{
  return name_;
}

bool stepanchenko::CrossRefs::hasKey(const std::string& key)
{
  return (this->search(key) != this->end());
}

std::list< size_t > stepanchenko::CrossRefs::getList(const std::string & key) const
{
  return this->search(key)->second;
}

size_t stepanchenko::CrossRefs::getSize() const
{
  return table_.bucket_count();
}

void stepanchenko::CrossRefs::removeEntry(const std::string& key)
{
  auto iter = this->search(key);
  table_.erase(iter);
}

void stepanchenko::CrossRefs::extend(const std::string& key, std::pair < size_t, std::string >& line)
{
  auto bucket = this->table_.find(key);
  bucket->second.push_back(line.first + lines_.size());
  std::pair < size_t, std::string > t_line = line;
  t_line.first += lines_.size();
  lines_.push_back(t_line);
}

