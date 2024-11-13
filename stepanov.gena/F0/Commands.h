#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

namespace stepanov
{ 
  void input(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& fileName);
  void output(const std::map<std::string, TextMap>& textMaps, const std::string& mapName);
  void merge(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2);
}

#endif 