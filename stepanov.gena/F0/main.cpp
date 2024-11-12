#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;
std::map<std::string, TextMap> textMaps;

void processWord(const std::string& word, size_t lineNumber, size_t& wordNumber, TextMap& map)
{
  map.emplace(word, std::make_pair(lineNumber, wordNumber));
  ++wordNumber;
}

void input(const std::string& mapName, const std::string& fileName)
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
    std::istringstream lineStream(line);
    size_t wordNumber = 0;
    std::for_each(std::istream_iterator<std::string>(lineStream),
            std::istream_iterator<std::string>(),
            std::bind(processWord, std::placeholders::_1, lineNumber, std::ref(wordNumber), std::ref(map)));
    ++lineNumber;
  }

  if (map.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  textMaps[mapName] = map;
}

void outputLine(const std::pair<const std::string&, const std::pair<size_t, size_t>>& entry, std::vector<std::string>& lines) {
  auto word = entry.first;
  auto indices = entry.second;
  size_t lineNum = indices.first;
  if (lines.size() <= lineNum)
  {
    lines.resize(lineNum + 1);
  }
  lines[lineNum] += (lines[lineNum].empty() ? "" : " ") + word;
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
  std::vector<std::string> lines;
  std::for_each(map.begin(), map.end(),
          std::bind(outputLine, std::placeholders::_1, std::ref(lines)));

  std::for_each(lines.begin(), lines.end(), [](const std::string& l)
  {
    std::cout << l << "\n";
  });
}

int main() {
  input("example", "input.txt");
  output("example");

  return 0;
}
