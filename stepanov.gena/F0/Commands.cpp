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

void extractAndProcessWord(const char&, std::string::const_iterator& start, std::string::const_iterator& end, 
               size_t lineNumber, size_t& wordNumber, TextMap& map)
{
  auto wordEnd = std::find(start, end, ' ');
  if (start != wordEnd)
  {
  std::string word(start, wordEnd);
  processWord(word, lineNumber, wordNumber, map);
  }
  start = (wordEnd == end) ? wordEnd : std::next(wordEnd);
}

void splitLineIntoWords(const std::string& line, size_t lineNumber, TextMap& map)
{
  size_t wordNumber = 0;
  auto start = line.begin();
  using namespace std::placeholders;
  auto boundExtractAndProcessWord = std::bind(extractAndProcessWord, _1, std::ref(start), line.end(), lineNumber, std::ref(wordNumber), std::ref(map));
  std::for_each(line.begin(), line.end(), boundExtractAndProcessWord);
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

void mergeEntries(TextMap& map3, 
                  TextMap::const_iterator& it1, 
                  TextMap::const_iterator& it2, 
                  const TextMap& map1, const TextMap& map2)
{
  if (it1 != map1.end())
  {
    auto toEmpl = it1->second;
    (toEmpl.first) *= 2;
    map3.emplace(it1->first, toEmpl);
    ++it1;
  }
  
  if (it2 != map2.end())
  {
    auto toEmpl = it2->second;
    (toEmpl.first) *= 2;
    (toEmpl.first) += 1;
    map3.emplace(it2->first, toEmpl);
    ++it2;
  }
}

void stepanov::merge(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2)
{
  auto map1It = textMaps.find(mapName1);
  auto map2It = textMaps.find(mapName2);

  if (map1It == textMaps.end() || map2It == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const TextMap& map1 = map1It->second;
  const TextMap& map2 = map2It->second;

  TextMap map3;

  auto it1 = map1.begin();
  auto it2 = map2.begin();

  while (it1 != map1.end() || it2 != map2.end())
  {
    mergeEntries(map3, it1, it2, map1, map2);
  }

  textMaps[mapName3] = map3;
}

