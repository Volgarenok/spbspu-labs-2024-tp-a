#include "Commands.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>


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

  for (const auto& entry : map)
  {
    const std::string& word = entry.first;
    size_t lineNum = entry.second.first;
    size_t wordPos = entry.second.second;
    lines[lineNum].push_back({word, wordPos});
  }

  for (auto& lineEntry : lines)
  {
    std::sort(lineEntry.second.begin(), lineEntry.second.end(),
         [](const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b) {
           return a.second < b.second;
         });
  }

  for (const auto& lineIt : lines) {
    for (size_t i = 0; i < lineIt.second.size(); ++i)
    {
      std::cout << lineIt.second[i].first;
      if (i < lineIt.second.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
  }
}