#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>
#include <ostream>

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

namespace stepanov
{ 
  void input(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& fileName); //1
  void output(const std::map<std::string, TextMap>& textMaps, const std::string& mapName, std::ostream& out); //2
  void merge(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2); //7
  void addLine(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& str, size_t pos); //3
  void add(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2); //4
  void remove(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& word); //5
  void swapStr(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const size_t& pos1, const size_t& pos2); //6
  void intersection(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2); //8
  void deleteMap(std::map<std::string, TextMap>& textMaps, const std::string& mapName); //9
  void substract(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2); //10
  void delByWord(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& word); //11
  void change(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& word1, const std::string& word2); //12
  void output(const std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& fileName); //13

}

#endif 