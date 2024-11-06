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
