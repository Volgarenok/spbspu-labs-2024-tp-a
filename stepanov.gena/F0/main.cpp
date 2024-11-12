#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;
std::map<std::string, TextMap> textMaps;

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

  while (end < line.length())
  {
    while (end < line.length() && line[end] != ' ') ++end;
    if (end > start) {
      processWord(line.substr(start, end - start), lineNumber, wordNumber, map);
    }
    end++;
    start = end;
  }
}

void input(const std::string& mapName, const std::string& fileName) {
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
  } else
  {
    textMaps[mapName] = map;
  }
}

void output(const std::string& mapName)
{
  auto it = textMaps.find(mapName);
  if (it == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const TextMap& map = it->second;
  std::map<size_t, std::vector<std::string>> lines;

  for (const auto& entry : map)
  {
    const std::string& word = entry.first;
    size_t lineNum = entry.second.first;
    lines[lineNum].push_back(word);
  }

  for (auto& lineEntry : lines)
  {
    std::sort(lineEntry.second.begin(), lineEntry.second.end());
  }

  for (auto lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
  {
    const std::vector<std::string>& words = lineIt->second;
    for (size_t i = 0; i < words.size(); ++i)
    {
      std::cout << words[i];
      if (i < words.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  // Тестирование команды INPUT
  std::cout << "Testing INPUT command:\n";
  input("map1", "input.txt");
  output("map1");

  return 0;
}
