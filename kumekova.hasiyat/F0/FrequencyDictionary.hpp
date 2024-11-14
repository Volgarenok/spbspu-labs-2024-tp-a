#ifndef FREQUENCYDICTIONARY_HPP
#define FREQUENCYDICTIONARY_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace kumekova
{
  class FrequencyDictionary
  {
  private:
    std::unordered_map<std::string, int> wordCount;

  public:
    void insert(const std::string &key);
    bool search(const std::string &key) const;
    int count(const std::string &key) const;
    void remove(const std::string &key);
    void decrease(const std::string &key, int count);
    double median() const;
    static double medianAcrossDictionaries(const std::unordered_map<std::string,
                                           FrequencyDictionary> &dictionaries);
    void loadFromFile(const std::string &filename);
    void clear();
    void stats() const;
    void print() const;
    double average() const;
    std::vector<std::pair<std::string, int>> top(size_t N) const;
    std::vector<std::string> getKeys() const;
};
}

#endif
