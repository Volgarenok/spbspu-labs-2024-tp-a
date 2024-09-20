#include "CrossRefs.hpp"

#include <unordered_map>
#include <iterator>
#include <string>
#include <algorithm>

std::unordered_map<std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::begin()
{
  return table_.begin();
}

std::unordered_map<std::string, std::list< size_t > >::iterator stepanchenko::CrossRefs::end()
{
  return table_.end();
}

std::unordered_map<std::string, std::list< size_t > >::const_iterator stepanchenko::CrossRefs::search(const std::string& word) const
{
  return table_.find(word);
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

    std::for_each(std::istream_iterator<std::string>(stream),
      std::istream_iterator<std::string>(), [&](const std::string& word) {
        std::string lowerWord;
        std::copy_if(word.begin(), word.end(), std::back_inserter(lowerWord), isalpha);
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
        insert(lowerWord, lineNumber);
      }
    );
    ++lineNumber;
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

std::vector< std::pair < size_t, std::string > > stepanchenko::CrossRefs::getLines()
{
  return lines_;
}

void stepanchenko::CrossRefs::removeEntry(const std::string& key)
{
  auto iter = this->search(key);
  table_.erase(iter);
}
