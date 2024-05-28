#ifndef INPUT_DICT_HPP
#define INPUT_DICT_HPP

#include <unordered_map>
#include <iostream>

namespace namestnikov
{
  std::unordered_map< std::string, std::string > inputDict(std::istream & in);
}

#endif