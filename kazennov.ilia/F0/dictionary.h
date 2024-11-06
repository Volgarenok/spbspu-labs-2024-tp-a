#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Delimiter.h"

namespace kazennov
{
  struct WordForInput
  {
    std::string word_;
  };
  struct FrequencyDict
  {
    std::map< std::string, unsigned int> dict_;
  };
  struct VectorOfDicts
  {
    std::vector< WordForInput > words_;
  };
  std::istream& operator>>(std::istream& in, WordForInput& word);
  std::istream& operator>>(std::istream& in, VectorOfDicts& word);
  bool operator>(const FrequencyDict& f, const FrequencyDict& other);
}
#endif
