#include "helping_commands.hpp"

void sakovskaia::saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end)
{
  if (it == end)
  {
    return;
  }
  file << it->first << " " << it->second << "\n";
  saveDictToFile(file, ++it, end);
}
