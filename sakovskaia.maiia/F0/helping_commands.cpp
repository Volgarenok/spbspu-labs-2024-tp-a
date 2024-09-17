#include "helping_commands.hpp"

void sakovskaia::saveDictToFile(std::ofstream & file, sakovskaia::dict_t::const_iterator it, sakovskaia::dict_t::const_iterator end)
{
  if (it == end)
  {
    return;
  }
  file << it->first << " " << it->second << "\n";
  sakovskaia::saveDictToFile(file, ++it, end);
}

void sakovskaia::updateFrequencies(sakovskaia::dict_t::iterator it, sakovskaia::dict_t::iterator end, int totalWords)
{
  if (it == end)
  {
    return;
  }
  it->second = 1 / totalWords;
  sakovskaia::updateFrequencies(++it, end, totalWords);
}

int sakovskaia::calculateTotalFrequencyExcludeOne(sakovskaia::dict_t::iterator it, sakovskaia::dict_t::iterator end, int excludeFrequency)
{
  if (it == end)
  {
    return 0;
  }
  if (it->second == excludeFrequency)
  {
    return sakovskaia::calculateTotalFrequencyExcludeOne(++it, end, excludeFrequency);
  }
  return it->second + sakovskaia::calculateTotalFrequencyExcludeOne(++it, end, excludeFrequency);
}

void sakovskaia::updateFrequenciesWithNew(sakovskaia::dict_t::iterator it, sakovskaia::dict_t::iterator end, int totalFrequency, int excludeWordFrequency)
{
  if (it == end)
  {
    return;
  }
  if (it->second != excludeWordFrequency)
  {
    it->second = (1 / totalFrequency) * it->second;
  }
  sakovskaia::updateFrequenciesWithNew(++it, end, totalFrequency, excludeWordFrequency);
}

int sakovskaia::calculateTotalFrequencyForTwo(sakovskaia::dict_t::iterator it1, sakovskaia::dict_t::iterator end1, sakovskaia::dict_t::iterator it2, sakovskaia::dict_t::iterator end2)
{
  if (it1 == end1 && it2 == end2)
  {
    return 0;
  }
  int freq1 = (it1 != end1) ? it1->second : 0;
  int freq2 = (it2 != end2) ? it2->second : 0;
  return freq1 + freq2 + sakovskaia::calculateTotalFrequencyForTwo((it1 != end1) ? ++it1 : it1, end1, (it2 != end2) ? ++it2 : it2, end2);
}

void sakovskaia::combineDictionaries(sakovskaia::dict_t::iterator it1, sakovskaia::dict_t::iterator end1, sakovskaia::dict_t::iterator it2, sakovskaia::dict_t::iterator end2, sakovskaia::dict_t & resultDict, int totalFrequency)
{
  if (it1 == end1 && it2 == end2)
  {
    return;
  }
  if (it1 != end1)
  {
    resultDict[it1->first] = (static_cast< double >(it1->second) / totalFrequency) * 100;
    sakovskaia::combineDictionaries(++it1, end1, it2, end2, resultDict, totalFrequency);
    return;
  }
  if (it2 != end2)
  {
    resultDict[it2->first] = (static_cast< double >(it2->second) / totalFrequency) * 100;
    sakovskaia::combineDictionaries(it1, end1, ++it2, end2, resultDict, totalFrequency);
  }
}

int sakovskaia::calculateTotalFrequency(sakovskaia::dict_t::iterator it, sakovskaia::dict_t::iterator end)
{
  if (it == end)
  {
    return 0;
  }
  return it->second + sakovskaia::calculateTotalFrequency(++it, end);
}

void sakovskaia::createDiffDictionary(sakovskaia::dict_t::iterator it1, sakovskaia::dict_t::iterator end1, sakovskaia::dict_t & dict2, sakovskaia::dict_t & resultDict, int totalFrequency)
{
  if (it1 == end1)
  {
    return;
  }
  auto it2 = dict2.find(it1->first);
  if (it2 == dict2.end() || it1->second > it2->second)
  {
    resultDict[it1->first] = static_cast< double >(it1->second) / totalFrequency;
  }
  sakovskaia::createDiffDictionary(++it1, end1, dict2, resultDict, totalFrequency);
}
