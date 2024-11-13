#include "Commands.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <iterator>


using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

void addWordToMap(const std::string& word, size_t lineNumber, size_t& wordNumber, TextMap& map)
{
  map.emplace(word, std::make_pair(lineNumber, wordNumber));
  ++wordNumber;
}

void processWord(const std::string& word, size_t lineNumber, size_t& wordNumber, TextMap& map)
{
  addWordToMap(word, lineNumber, wordNumber, map);
}

void splitLineIntoWords(const std::string& line, size_t lineNumber, TextMap& map)
{
  size_t wordNumber = 0;
  auto start = line.begin();

  std::for_each(line.begin(), line.end(), [&](char) {
    auto end = std::find(start, line.end(), ' ');
    if (start != end) {
      std::string word(start, end);
      processWord(word, lineNumber, wordNumber, map);
    }
    start = (end == line.end()) ? end : std::next(end);
  });
}

void processLine(const std::string& line, size_t& lineNumber, TextMap& map)
{
  splitLineIntoWords(line, lineNumber, map);
  ++lineNumber;
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
    processLine(line, lineNumber, map);
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

void populateLines(std::map<size_t, std::vector<std::pair<std::string, size_t>>>& lines,
           const std::pair<const std::string, std::pair<size_t, size_t>>& entry)
{
  const std::string& word = entry.first;
  size_t lineNum = entry.second.first;
  size_t wordPos = entry.second.second;
  lines[lineNum].push_back({word, wordPos});
}

bool compareByWordPos(const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b)
{
  return a.second < b.second;
}

void sortLineEntries(std::pair<const size_t, std::vector<std::pair<std::string, size_t>>>& lineEntry)
{
  using namespace std::placeholders;
  auto comp = std::bind(compareByWordPos, _1, _2);
  std::sort(lineEntry.second.begin(), lineEntry.second.end(), comp);
}

void printLine(const std::pair<const size_t, std::vector<std::pair<std::string, size_t>>>& lineIt)
{
  for (size_t i = 0; i < lineIt.second.size(); ++i)
  {
  std::cout << lineIt.second[i].first;
  if (i < lineIt.second.size() - 1)
  {
    std::cout << " ";
  }
  }
  std::cout << "\n";
}

void stepanov::output(const std::map<std::string, TextMap>& textMaps, const std::string& mapName)
{
  using namespace std::placeholders;
  auto it = textMaps.find(mapName);
  if (it == textMaps.end())
  {
  std::cout << "<INVALID COMMAND>\n";
  return;
  }

  const TextMap& map = it->second;
  std::map<size_t, std::vector<std::pair<std::string, size_t>>> lines;

  std::for_each(map.begin(), map.end(), std::bind(populateLines, std::ref(lines), _1));
  std::for_each(lines.begin(), lines.end(), std::bind(sortLineEntries, _1));
  std::for_each(lines.begin(), lines.end(), std::bind(printLine,_1));
}