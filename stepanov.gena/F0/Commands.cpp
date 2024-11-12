#include "Commands.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

void processWord(const std::string& word, size_t lineNumber, size_t& wordNumber, TextMap& map)
{
 map.emplace(word, std::make_pair(lineNumber, wordNumber));
 ++wordNumber;
}

void splitLineIntoWords(const std::string& line, size_t lineNumber, TextMap& map)
{
 size_t wordNumber = 0;
 size_t start = 0;
 size_t end = 0;

 while (end < line.length()) {
  while (end < line.length() && line[end] != ' ') ++end;
  if (end > start)
  {
   processWord(line.substr(start, end - start), lineNumber, wordNumber, map);
  }
  end++;
  start = end;
 }
}

void stepanov::input(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& fileName)
{
 if (textMaps.find(mapName) != textMaps.end())
 {
  std::cout << "<INVALID COMMAND>\n";
  return;
 }

 std::ifstream file(fileName);
 if (!file.is_open())
 {
  std::cout << "<INVALID COMMAND>\n";
  return;
 }

 TextMap map;
 std::string line;
 size_t lineNumber = 0;

 while (std::getline(file, line))
 {
  splitLineIntoWords(line, lineNumber, map);
  ++lineNumber;
 }

 if (map.empty())
 {
  std::cout << "<INVALID COMMAND>\n";
 }
 else
 {
  textMaps[mapName] = map;
 }
}

void stepanov::output(const std::map<std::string, TextMap>& textMaps, const std::string& mapName)
{
  auto it = textMaps.find(mapName);
  if (it == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const TextMap& map = it->second;
  std::map<size_t, std::vector<std::pair<std::string, size_t>>> lines;

  std::for_each(map.begin(), map.end(), [&lines](const auto& entry) {
    const std::string& word = entry.first;
    size_t lineNum = entry.second.first;
    size_t wordPos = entry.second.second;
    lines[lineNum].push_back({word, wordPos});
  });

  std::for_each(lines.begin(), lines.end(), [](auto& lineEntry) {
    std::sort(lineEntry.second.begin(), lineEntry.second.end(),
      [](const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b) {
        return a.second < b.second;
      });
  });

  std::for_each(lines.begin(), lines.end(), [](const auto& lineIt) {
    std::for_each(lineIt.second.begin(), lineIt.second.end(), [&lineIt](const auto& wordPair) {
      std::cout << wordPair.first;
      if (&wordPair != &lineIt.second.back()) std::cout << " ";
    });
    std::cout << "\n";
  });
}