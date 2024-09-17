#include "helping_commands.hpp"

void sakovskaia::saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end)
{
  if (it == end)
  {
    return;
  }
  file << it->first << " " << it->second << "\n";
  saveDictToFile(file, ++it, end);
}

void sakovskaia::updateFrequencies(dict_t::iterator it, dict_t::iterator end, int totalWords)
{
  if (it == end)
  {
    return;
  }
  it->second = 1 / totalWords;
  updateFrequencies(++it, end, totalWords);
}

int sakovskaia::calculateTotalFrequencyExcludeOne(dict_t::iterator it, dict_t::iterator end, int excludeFrequency)
{
  if (it == end)
  {
    return 0;
  }
  if (it->second == excludeFrequency)
  {
    return calculateTotalFrequency(++it, end, excludeFrequency);
  }
  return it->second + calculateTotalFrequency(++it, end, excludeFrequency);
}

void sakovskaia::updateFrequenciesWithNew(dict_t::iterator it, dict_t::iterator end, int totalFrequency, int excludeWordFrequency)
{
  if (it == end)
  {
    return;
  }
  if (it->second != excludeWordFrequency)
  {
    it->second = (1 / totalFrequency) * it->second;
  }
  updateFrequenciesWithNew(++it, end, totalFrequency, excludeWordFrequency);
}

int sakovskaia::calculateTotalFrequencyForTwo(dict_t::iterator it1, dict_t::iterator end1, dict_t::iterator it2, dict_t::iterator end2)
{
  if (it1 == end1 && it2 == end2)
  {
    return 0;
  }
  int freq1 = (it1 != end1) ? it1->second : 0;
  int freq2 = (it2 != end2) ? it2->second : 0;
  return freq1 + freq2 + calculateTotalFrequencyForTwo((it1 != end1) ? ++it1 : it1, end1, (it2 != end2) ? ++it2 : it2, end2);
}

void sakovskaia::combineDictionaries(dict_t::iterator it1, dict_t::iterator end1, dict_t::iterator it2, dict_t::iterator end2, dict_t & resultDict, int totalFrequency)
{
  if (it1 == end1 && it2 == end2)
  {
    return;
  }
  if (it1 != end1)
  {
    resultDict[it1->first] = (static_cast< double >(it1->second) / totalFrequency) * 100;
    combineDictionaries(++it1, end1, it2, end2, resultDict, totalFrequency);
    return;
  }
  if (it2 != end2)
  {
    resultDict[it2->first] = (static_cast< double >(it2->second) / totalFrequency) * 100;
    combineDictionaries(it1, end1, ++it2, end2, resultDict, totalFrequency);
  }
}

int sakovskaia::calculateTotalFrequency(dict_t::iterator it, dict_t::iterator end)
{
  if (it == end)
  {
    return 0;
  }
  return it->second + calculateTotalFrequency(++it, end);
}

void sakovskaia::createDiffDictionary(dict_t::iterator it1, dict_t::iterator end1, dict_t & dict2, dict_t & resultDict, int totalFrequency)
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
  createDiffDictionary(++it1, end1, dict2, resultDict, totalFrequency);
}
