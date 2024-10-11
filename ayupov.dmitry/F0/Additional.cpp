#include "Additional.hpp"

void ayupov::isDict(const std::map< std::string, ARDictionary >& dicts, const std::string& dict)
{
  if (dicts.find(dict) == dicts.end())
  {
    throw std::logic_error("NO SUCH DICTIONARY");
  }
}
