#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>

namespace kazennov
{
  struct FrequencyDict
  {
    std::map< std::string, unsigned int> > dict_;
  };
}
