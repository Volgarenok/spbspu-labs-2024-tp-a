#include "FrequencyDictionary.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>

void kumekova::FrequencyDictionary::insert(const std::string &key)
{
  if (key.empty())
    throw std::invalid_argument("Key cannot be empty");
  wordCount[key]++;
}

bool kumekova::FrequencyDictionary::search(const std::string &key) const
{
  return wordCount.find(key) != wordCount.end();
}

int kumekova::FrequencyDictionary::count(const std::string &key) const
{
  auto it = wordCount.find(key);
  return it != wordCount.end() ? it->second : 0;
}

void kumekova::FrequencyDictionary::remove(const std::string &key)
{
  auto it = wordCount.find(key);
  if (it != wordCount.end())
  {
    wordCount.erase(it);
  }
  else
  {
    throw std::invalid_argument("Key not found");
  }
}

void kumekova::FrequencyDictionary::decrease(const std::string &key,
                                               int count)
{
  if (count < 0)
    throw std::invalid_argument("Count cannot be negative");
  auto it = wordCount.find(key);
  if (it != wordCount.end())
  {
    it->second -= count;
    if (it->second < 0)
      it->second = 0;
  }
  else
  {
    throw std::invalid_argument("Key not found");
  }
}

double kumekova::FrequencyDictionary::median() const
{
  if (wordCount.empty())
    throw std::runtime_error("The dictionary is empty.");

  std::vector<int> frequencies;
  for (const auto &pair : wordCount)
  {
    frequencies.push_back(pair.second);
  }

  std::sort(frequencies.begin(), frequencies.end());

  size_t size = frequencies.size();
  if (size % 2 == 0)
  {
    return (frequencies[size / 2 - 1] + frequencies[size / 2]) / 2.0;
  }
  else
  {
    return frequencies[size / 2];
  }
}

double kumekova::FrequencyDictionary::medianAcrossDictionaries(
    const std::unordered_map<std::string, FrequencyDictionary> &dictionaries)
{
  std::vector<int> allFrequencies;

  for (const auto &pair : dictionaries)
  {
    const auto &frequencies = pair.second.wordCount;
    for (const auto &freqPair : frequencies)
    {
      allFrequencies.push_back(freqPair.second);
    }
  }

  if (allFrequencies.empty())
    throw std::runtime_error(
        "No frequencies found in the provided dictionaries.");

  std::sort(allFrequencies.begin(), allFrequencies.end());

  size_t size = allFrequencies.size();
  if (size % 2 == 0)
  {
    return (allFrequencies[size / 2 - 1] + allFrequencies[size / 2]) / 2.0;
  }
  else
  {
    return allFrequencies[size / 2];
  }
}

void kumekova::FrequencyDictionary::loadFromFile(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
    throw std::runtime_error("Could not open file");
  std::string word;

  while (file >> word)
  {
    insert(word);
  }
}

void kumekova::FrequencyDictionary::clear()
{
  wordCount.clear();
}

void kumekova::FrequencyDictionary::stats() const
{
  std::cout << "Total unique words: " << wordCount.size() << std::endl;
}

void kumekova::FrequencyDictionary::print() const
{
  if (wordCount.empty())
  {
    throw std::runtime_error("The dictionary is empty.");
  }

  for (const auto &pair : wordCount)
  {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
}

double kumekova::FrequencyDictionary::average() const
{
  if (wordCount.empty())
    return 0.0;

  int totalFrequency = 0;
  for (const auto &pair : wordCount)
  {
    totalFrequency += pair.second;
  }
  return static_cast<double>(totalFrequency) / wordCount.size();
}

std::vector<std::pair<std::string, int>>
kumekova::FrequencyDictionary::top(size_t N) const
{
  std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(),
                                                       wordCount.end());
  std::sort(sortedWords.begin(), sortedWords.end(),
            [](const auto &a, const auto &b)
            {
              return a.second > b.second;
            });

  if (N > sortedWords.size())
    N = sortedWords.size();
  return std::vector<std::pair<std::string, int>>(sortedWords.begin(),
                                                  sortedWords.begin() + N);
}

std::vector<std::string> kumekova::FrequencyDictionary::getKeys() const
{
  std::vector<std::string> keys;
  std::transform(wordCount.begin(), wordCount.end(), std::back_inserter(keys),
                 [](const auto &pair)
                 {
                   return pair.first;
                 });
  return keys;
}
