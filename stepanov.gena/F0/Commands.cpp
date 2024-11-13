#include "Commands.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <functional>
#include <iterator>


using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;
using pair_t = std::pair<const std::string, std::pair<size_t, size_t>>;

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

void updateLineNumbersToMerge(pair_t& entry, size_t n)
{
  entry.second.first = entry.second.first * 2 + n;
}

void stepanov::merge(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2)
{
  using namespace std::placeholders;
  auto map1It = textMaps.find(mapName1);
  auto map2It = textMaps.find(mapName2);

  if (map1It == textMaps.end() || map2It == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  TextMap tempMap1 = map1It->second;
  TextMap map3 = map2It->second;
  std::for_each(tempMap1.begin(), tempMap1.end(), std::bind(updateLineNumbersToMerge, _1, 0));
  std::for_each(map3.begin(), map3.end(), std::bind(updateLineNumbersToMerge, _1, 1));
  map3.insert(tempMap1.begin(), tempMap1.end());
  textMaps[mapName3] = map3;
}

void updateLineNumbers(pair_t& entry, const size_t& pos, const size_t& n)
{
  size_t& lineNum = entry.second.first;
  lineNum = lineNum >= pos ? lineNum + n : lineNum;
}

void getMaxLineNum(const pair_t& entry, size_t& pos)
{
  pos = std::max(entry.second.first, pos);
}

void stepanov::addLine(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& str, size_t pos)
{
  using namespace std::placeholders;
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  TextMap& map = mapIt->second;
  size_t maxPos = 0;
  std::for_each(map.cbegin(), map.cend(), std::bind(getMaxLineNum, _1, std::ref(maxPos)));
  pos = maxPos < pos ? maxPos : pos;
  std::for_each(map.begin(), map.end(), std::bind(updateLineNumbers, _1, pos, 1));
  processLine(str, pos, map);
}

void stepanov::add(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2)
{
  using namespace std::placeholders;
  auto map1It = textMaps.find(mapName1);
  auto map2It = textMaps.find(mapName2);

  if (map1It == textMaps.end() || map2It == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const TextMap& map1 = map1It->second;
  TextMap map3 = map2It->second;

  size_t maxMap1Pos = 0;
  std::for_each(map1.cbegin(), map1.cend(), std::bind(getMaxLineNum, _1, std::ref(maxMap1Pos)));
  std::for_each(map3.begin(), map3.end(), std::bind(updateLineNumbers, _1, 0, maxMap1Pos));
  map3.insert(map1.begin(), map1.end());

  textMaps[mapName3] = map3;
}

void stepanov::remove(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& str)
{
  using namespace std::placeholders;
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  TextMap& map = mapIt->second;
  auto toErase = map.find(str);
  if (toErase == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  map.erase(map.find(str));
}


void swapIndex(pair_t& entry, const size_t& pos1, const size_t& pos2)
{
  size_t& lineNum = entry.second.first;
  if (lineNum == pos1)
  {
    lineNum = pos2;
    return;
  }
  if (lineNum == pos2)
  {
    lineNum = pos1;
  }
}

void stepanov::swapStr(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const size_t& pos1, const size_t& pos2)
{
  using namespace std::placeholders;
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  TextMap& map = mapIt->second;
  size_t maxPos = 0;
  std::for_each(map.cbegin(), map.cend(), std::bind(getMaxLineNum, _1, std::ref(maxPos)));
  if (maxPos < pos1 || maxPos < pos2)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  std::for_each(map.begin(), map.end(), std::bind(swapIndex, _1, pos1, pos2));
}

bool findIntersec(const pair_t& entry, const TextMap& map2)
{
  auto it = map2.find(entry.first);
  if (it != map2.end())
  {
    if (it->second == entry.second)
    {
      return true;
    }
  }
  return false;
}

void stepanov::intersection(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2)
{
  using namespace std::placeholders;
  
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
  std::copy_if(map1.begin(), map1.end(), std::inserter(map3, map3.begin()), std::bind(findIntersec, _1, map2));
  textMaps[mapName3] = map3;
}

void stepanov::deleteMap(std::map<std::string, TextMap>& textMaps, const std::string& mapName)
{
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  textMaps.erase(mapIt);
}


bool findSubstract(const pair_t& entry, const TextMap& map2)
{
  return !findIntersec(entry, map2);
}

void stepanov::substract(std::map<std::string, TextMap>& textMaps, const std::string& mapName3, const std::string& mapName1, const std::string& mapName2)
{
  using namespace std::placeholders;
  
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
  std::copy_if(map1.begin(), map1.end(), std::inserter(map3, map3.begin()), std::bind(findSubstract, _1, map2));
  textMaps[mapName3] = map3;
}

void collectLineNumbersWithWord(const pair_t& entry, const std::string& word, std::set<size_t>& lineNumbers)
{
  if (entry.first == word)
  {
    lineNumbers.insert(entry.second.first);

  }
}

void deleteEntriesByLineNumber(pair_t& entry, const std::set<size_t>& lineNumbers, TextMap& map)
{
  if (lineNumbers.find(entry.second.first) != lineNumbers.end())
  {
    map.erase(entry.first);
  }
}

void stepanov::delByWord(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& word)
{
  using namespace std::placeholders;
  
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  TextMap& map = mapIt->second;
  if (map.find(word) == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  std::set<size_t> lineNumbers;

  std::for_each(map.begin(), map.end(), std::bind(collectLineNumbersWithWord, _1, word, std::ref(lineNumbers)));
  std::for_each(map.begin(), map.end(), std::bind(deleteEntriesByLineNumber, _1, lineNumbers, std::ref(map)));
}

pair_t changeWord(const pair_t& entry, const std::string& word1, const std::string& word2)
{
  auto ind = entry.second;
  if (entry.first == word1)
  {
    return make_pair(word2, ind);
  }
  if (entry.first == word2)
  {
    return make_pair(word1, ind);
  }
  return entry;
}

void stepanov::change(std::map<std::string, TextMap>& textMaps, const std::string& mapName, const std::string& word1, const std::string& word2)
{
  using namespace std::placeholders;
  auto mapIt = textMaps.find(mapName);
  if (mapIt == textMaps.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  TextMap& map = mapIt->second;
  if (map.find(word1) == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (map.find(word2) == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  TextMap tempMap;
}
