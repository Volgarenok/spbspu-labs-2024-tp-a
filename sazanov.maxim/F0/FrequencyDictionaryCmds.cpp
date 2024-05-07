#include "FrequencyDictionaryCmds.hpp"
#include <unordered_map>
#include <sstream>

void sazanov::insert(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{

  std::string dict;
  in >> dict;
  std::string word;
  in >> word;
  if (!in || collection.find(dict) == collection.end() || word.empty())
  {
    out << "INVALID COMMAND";
    return;
  }

  ++collection[dict][word];
}
