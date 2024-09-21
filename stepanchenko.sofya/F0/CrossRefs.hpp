#ifndef CROSS_REFS_HPP
#define CROSS_REFS_HPP

#include <unordered_map>
#include <string>
#include <iterator>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <list>

namespace stepanchenko
{
  class CrossRefs
  {
  public:
    CrossRefs() = default;
    ~CrossRefs() = default;
    CrossRefs(const CrossRefs& other) = default;
    CrossRefs(CrossRefs&& moved) noexcept = default;

    std::unordered_map<std::string, std::list< size_t > >::iterator begin();
    std::unordered_map<std::string, std::list< size_t > >::iterator end();
    std::unordered_map<std::string, std::list< size_t > >::const_iterator search(const std::string& word) const;

    void createTable(const std::string& tableName, const std::string& fname);
    void append(const std::string& fname);
    void insert(const std::pair < std::string, std::list< size_t > > bucket);
    void print(std::ostream& out);

    const std::string getName() const;
    std::list< size_t > getList(const std::string& key) const;
    const size_t getSize() const;

    bool hasKey(const std::string& key);
    void removeEntry(const std::string& key);
    void extend(const std::string& key, std::pair < size_t, std::string >& lines);

    bool operator==(const CrossRefs& cr) const;
    bool operator<(const CrossRefs& cr) const;

    friend std::istream& operator>>(std::istream& in, CrossRefs& cr);

    std::vector< std::pair < size_t, std::string > > lines_;
  private:
    std::unordered_map< std::string, std::list< size_t > > table_;
    std::string name_;

    void insert(const std::string& word, const size_t& lineNumber)
    {
      auto iter = table_.find(word);
      if (iter != table_.end())
      {
        iter->second.push_back(lineNumber);
      }
      else
      {
        std::list< size_t > list;
        list.push_back(lineNumber);
        table_.insert({ word, list });
      }
    }
  };
}

#endif
