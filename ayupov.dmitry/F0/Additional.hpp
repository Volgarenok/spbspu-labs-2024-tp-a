#ifndef ADDITIONAL_HPP
#define ADDITIONAL_HPP

#include <string>
#include <map>

#include "Dictionary.hpp"

namespace ayupov
{
  void isDict(const std::map< std::string, ARDictionary >& dicts, const std::string& dict);
}

#endif
