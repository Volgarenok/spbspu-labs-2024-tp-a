#ifndef SUPPORT_CMDS_HPP
#define SUPPORT_CMDS_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "DictionaryLineIO.hpp"

namespace sazanov
{
  using FrequencyDictionary = std::unordered_map< std::string, size_t >;
  using DictionaryCollection = std::unordered_map< std::string, FrequencyDictionary >;

  void readDict(const std::string& dictName, const std::string& fileName, DictionaryCollection& dictionaries);
  bool isCorrectFile(const std::string& fileName);
}

#endif
