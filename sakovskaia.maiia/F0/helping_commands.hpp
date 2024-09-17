#ifndef HELPING_COMMADS_HPP
#define HELPING_COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>

namespace sakovskaia
{
  using dict_t = std::map< std::string, size_t >;
  void extendDict(dict_t & dict, std::istream & input);
  void saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end);
  void updateFrequencies(dict_t::iterator it, dict_t::iterator end, int totalWords);
  int calculateTotalFrequencyExcludeOne(dict_t::iterator it, dict_t::iterator end, int excludeFrequency);
  void updateFrequenciesWithNew(dict_t::iterator it, dict_t::iterator end, int totalFrequency, int excludeWordFrequency);
  int calculateTotalFrequencyForTwo(dict_t::iterator it1, dict_t::iterator end1, dict_t::iterator it2, dict_t::iterator end2);
  void combineDictionaries(dict_t::iterator it1, dict_t::iterator end1, dict_t::iterator it2, dict_t::iterator end2, dict_t & resultDict, int totalFrequency);
  int calculateTotalFrequency(dict_t::iterator it, dict_t::iterator end);
  void createDiffDictionary(dict_t::iterator it1, dict_t::iterator end1, dict_t & dict2, dict_t & resultDict, int totalFrequency);
}

#endif
