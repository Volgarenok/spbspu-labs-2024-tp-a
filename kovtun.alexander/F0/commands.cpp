#include "commands.hpp"

void kovtun::create(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName, fileName;
  in >> mapName >> fileName;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) != maps.end())
  {
    throw std::logic_error("map with name \"" + mapName + "\" already exists");
  }

  map_t newMap = map_t();
  readFile(newMap, fileName);

  maps[mapName] = newMap;
  out << mapName << ": created\n";
}

void kovtun::remove(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName;
  in >> mapName;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("nothing to remove");
  }

  maps.erase(mapName);
  out << mapName << ": removed\n";
}

void kovtun::recover(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string fileName, mapName;
  in >> fileName >> mapName;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("map with name \"" + mapName + "\" doesn't exist");
  }

  auto wordMap = maps[mapName];
  auto text = std::map< size_t, std::array< std::string, 200 > >();

  for (auto word_map_it = wordMap.cbegin(); word_map_it != wordMap.cend(); ++word_map_it)
  {
    auto word = word_map_it->first;
    auto lineMap = word_map_it->second;

    for (auto line_map_it = lineMap.cbegin(); line_map_it != lineMap.cend(); ++line_map_it)
    {
      size_t lineNum = line_map_it->first;
      auto positions = line_map_it->second;

      for (auto pos = positions.cbegin(); pos != positions.cend(); ++pos)
      {
        if (*pos > 200)
        {
          throw std::logic_error("oh no");
        }
        text[lineNum][(*pos) - 1] = word;
      }
    }
  }

  std::ofstream file;
  file.open(fileName);
  for (auto line : text)
  {
    for (auto t = line.second.cbegin(); t != line.second.cend(); ++t)
    {
      file << *t << " ";
    }
    file << "\n";
  }
  file.close();

  out << mapName << ": recovered\n";
}

void kovtun::search(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName, word;
  in >> mapName >> word;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("map not found");
  }

  auto map = maps[mapName];
  if (map.find(word) == map.end())
  {
    throw std::logic_error("word not found");
  }

  out << mapName << ": \"" << word << "\" occurs in " << map[word].size() << " lines\n";
}

void kovtun::replace(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName, word, newWord;
  in >> mapName >> word >> newWord;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("map not found");
  }

  auto map = maps[mapName];
  if (map.find(word) == map.end())
  {
    throw std::logic_error("word not found");
  }

  map[newWord] = map[word];
  map.erase(word);

  out << mapName << ": \"" << word << "\" replaced by \"" << newWord << "\"\n";
}

void kovtun::count(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName;
  in >> mapName;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("map not found");
  }

  out << mapName << ": " << maps[mapName].size() << " words\n";
}

void kovtun::flush(kovtun::cross_t & maps, std::istream & in, std::ostream & out)
{
  std::string mapName;
  in >> mapName;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("failed to read command arguments");
  }

  if (maps.find(mapName) == maps.end())
  {
    throw std::logic_error("map not found");
  }

  out << mapName << ":";
  for (auto it : maps[mapName])
  {
    out << " " << it.first;
  }
  out << "\n";
}

void kovtun::readFile(kovtun::map_t & map, std::string fileName)
{
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("failed to open the file");
  }

  size_t lineIndex = 1;
  size_t placeIndex = 1;

  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream stream(line);
    std::string word;
    placeIndex = 1;
    while (stream >> word)
    {
      while (!word.empty() && !std::isalnum(word.back()))
      {
        word.pop_back();
      }

      if (word.empty())
      {
        continue;
      }

      map[word][lineIndex].push_back(placeIndex);
      placeIndex++;
    }

    lineIndex++;
  }

  file.close();
}

void kovtun::showMap(kovtun::map_t & map)
{
  for (auto it = map.begin(); it != map.end(); ++it)
  {
    std::cout << it->first << ":\n";

    for (auto in_it = it->second.begin(); in_it != it->second.end(); ++in_it)
    {
      std::cout << "line: " << in_it->first << "\nplaces: ";

      for (auto place = in_it->second.begin(); place != in_it->second.end(); ++place)
      {
        std::cout << *place << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}
