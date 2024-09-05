#ifndef INPUT_OUTPUT_DATA_HPP
#define INPUT_OUTPUT_DATA_HPP

#include <unordered_map>
#include <fstream>

namespace namestnikov
{
  std::unordered_map< std::string, std::string > inputDict(std::ifstream & in);
  void outputDict(std::ofstream & out, const std::unordered_map< std::string, std::string > & dict);
}

#endif
