#include "dictionary.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

namespace kozlova
{
  Dictionary::Dictionary(const std::string& name) :
    name_(name)
  {}

  Dictionary::Dictionary(const std::map< std::string, size_t >& dictionary) :
    dictionary_(dictionary)
  {}

  std::string Dictionary::getName() const
  {
    return name_;
  }
}
