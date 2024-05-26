#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <map>
#include <istream>

namespace sivkov
{
  std::map< std::string, std::map< std::string, std::string > > inputDictionary(std::istream& in);
}
#endif

