#include "command.hpp"

void printSet(const std::set< int >& s)
{
  std::copy(s.begin(), s.end(), std::ostream_iterator< int >(std::cout, " "));
}

void processPair(const std::pair< const std::string, std::set< int > >& p)
{
  std::cout << p.first << " - ";
  printSet(p.second);
  std::cout << '\n';
}

bool compareSize(const std::pair< const std::string, std::set< int > >& p1, const std::pair< const std::string, std::set< int > >& p2)
{
  return p1.second.size() < p2.second.size();
}

void printIfMaxSize(const std::pair< const std::string, std::set< int > >& p, size_t maxSize)
{
  if (p.second.size() == maxSize)
  {
    std::cout << p.first << " ";
  }
}

void basko::topCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps)
{
  if (words.size() != 2)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  std::string name = words[1];
  auto it = maps.find(name);
  if (it == maps.end())
  {
    throw std::logic_error("There is no such dictionary");
  }

  const auto& resMap = it->second;
  if (resMap.empty())
  {
    throw std::logic_error("dict is empty");
  }
  auto maxIt = std::max_element(resMap.begin(), resMap.end(), compareSize);
  auto maxSize = maxIt->second.size();
  std::for_each(resMap.begin(), resMap.end(), [=](const auto& p) { printIfMaxSize(p, maxSize); });
  std::cout << maxSize << '\n';
}

void basko::Addcommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps)
{
  if (words.size() != 4)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  const std::string& word = words[2];
  if (!checkInt(words[3]))
  {
    throw std::logic_error("Wrong line number");
  }
  int number = std::stoi(words[3]);
  auto it = maps.find(name);
  if (it == maps.end())
  {
    throw std::logic_error("There is no such dictionary");
  }
  auto& wordSet = it->second[word];
  if (wordSet.contains(number))
  {
    throw std::logic_error("The word has already been added for the string");
  }
  wordSet.insert(number);
}

void basko::createDictCommand(const std::vector<std::string>& words, std::map<std::string, std::map<std::string, std::set<int>>>& maps)
{
  if (words.size() != 2 && words.size() != 3)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  std::string name = words[1];
  if (maps.contains(name))
  {
    throw std::logic_error("There's already a dictionary");
  }
  maps[name] = std::map<std::string, std::set<int>>();
  if (words.size() == 3)
  {
    std::string filename = words[2];
    readFile(maps[name], filename);
  }
}

void basko::removeCommand(const std::vector<std::string >& words, std::map<std::string, std::map< std::string, std::set< int >>>& maps)
{
  if (words.size() != 3)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  const std::string& word = words[2];
  auto mapIt = maps.find(name);
  if (mapIt == maps.end())
  {
    throw std::logic_error("There is no such dictionary");
  }
  auto& wordMap = mapIt->second;
  auto wordIt = wordMap.find(word);
  if (wordIt == wordMap.end())
  {
    throw std::logic_error("There is no such word");
  }
  wordMap.erase(wordIt);
  std::cout << "The word has been successfully deleted\n";
}

void basko::searchCommand(const std::vector< std::string>& words, std::map<std::string, std::map< std::string, std::set< int >>>& maps)
{
  if (words.size() != 3)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  const std::string& word = words[2];
  const auto mapIt = maps.find(name);
  if (mapIt == maps.end())
  {
    throw std::logic_error("There is no such dictionary");
  }
  const auto& wordMap = mapIt->second;
  const auto wordIt = wordMap.find(word);
  if (wordIt == wordMap.end())
  {
    throw std::logic_error("There is no such word");
  }
  const auto& numbers = wordIt->second;
  std::copy(numbers.begin(), numbers.end(), std::ostream_iterator< int >(std::cout, " "));
  std::cout << '\n';
}

void basko::showCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int >>>& maps)
{
  if (words.size() != 2)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const auto& name = words[1];
  if (!maps.contains(name))
  {
    throw std::logic_error("There is no such dictionary");
  }
  const auto& wordMap = maps[name];
  if (wordMap.empty())
  {
    throw std::logic_error("Dict is empty");
  }
  std::for_each(wordMap.begin(), wordMap.end(), processPair);
}

void basko::mergeCommand(const std::vector< std::string >& words, std::map< std::string, std::map<std::string, std::set< int >>>& maps)
{
  if (words.size() != 4)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& nameNewDict = words[1];
  const std::string& nameDict1 = words[2];
  const std::string& nameDict2 = words[3];
  if (!maps.contains(nameDict1) || !maps.contains(nameDict2))
  {
    throw std::logic_error("There is no such dictionary");
  }
  if (maps.contains(nameNewDict))
  {
    throw std::logic_error("There's already a dictionary");
  }
  const auto& map1 = maps[nameDict1];
  const auto& map2 = maps[nameDict2];
  std::map< std::string, std::set< int > > map3 = map1;
  for (const auto& [word, rows] : map2)
  {
    map3[word].insert(rows.begin(), rows.end());
  }
  maps[nameNewDict] = map3;
  std::cout << "Dictionary is created\n";
}

void basko::countWordsCommand(const std::vector<std::string>& words, std::map<std::string, std::map<std::string, std::set< int >>>& maps)
{
  if (words.size() != 2)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  if (!maps.contains(name))
  {
    throw std::logic_error("There is no such dictionary");
  }
  const auto& dict = maps[name];
  if (dict.empty())
  {
    throw std::logic_error("Dict is empty");
  }
  std::cout << "Total words = " << dict.size() << '\n';
}

void basko::clearCommand(const std::vector< std::string >& words, std::map< std::string, std::map<std::string, std::set< int >>>& maps)
{
  if (words.size() != 2)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  if (!maps.contains(name))
  {
    throw std::logic_error("There is no such dictionary");
  }
  auto& dict = maps[name];
  if (dict.empty())
  {
    throw std::logic_error("Dict is empty");
  }
  dict.clear();
}

void basko::matchWordsCommand(const std::vector<std::string>& words, std::map<std::string, std::map<std::string, std::set<int>>>& maps)
{
  if (words.size() != 2)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  const std::string& name = words[1];
  if (!maps.contains(name))
  {
    throw std::logic_error("There is no such dictionary");
  }
  const auto& dictionary = maps[name];
  if (dictionary.empty())
  {
    throw std::logic_error("Dict is empty");
  }
  std::map<std::string, std::set<int>> copy_map(dictionary.begin(), dictionary.end());
  std::for_each(copy_map.begin(), copy_map.end(), [&copy_map](const auto& p) {
    std::for_each(p.second.begin(), p.second.end(), [&p, &copy_map](int row) {
      std::vector<std::string> matchedWords{ p.first };

      std::for_each(copy_map.begin(), copy_map.end(), [&matchedWords, &row, &p](auto& t) {
        if (p.first != t.first && t.second.contains(row))
        {
          matchedWords.push_back(t.first);
          t.second.erase(row);
        }
        });

      if (matchedWords.size() > 1)
      {
      std::cout << row << ": ";
        std::for_each(matchedWords.begin(), matchedWords.end(), [](const std::string& word) {
          std::cout << word << " ";
          });
        std::cout << '\n';
      }
      });
    });
}

void basko::intersectionCommand(const std::vector<std::string >& words, std::map<std::string, std::map<std::string, std::set< int >>>& maps)
{
  if (words.size() != 4)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  if (!maps.contains(words[2]) || !maps.contains(words[3]))
  {
    throw std::logic_error("There's no such dictionary");
  }
  if (maps[words[2]].size() == 0 || maps[words[3]].size() == 0)
  {
    throw std::logic_error("Dict is empty");
  }
  if (maps.contains(words[1]))
  {
    throw std::logic_error("There's already a dictionary");
  }
  std::string nameNewMap = words[1];
  auto map1 = maps[words[2]];
  auto map2 = maps[words[3]];
  std::map< std::string, std::set< int > > res;
  for (auto p : map1)
  {
    if (map2.contains(p.first))
    {
      res[p.first] = p.second;
      res[p.first].insert(map2[p.first].begin(), map2[p.first].end());
    }
  }
  maps[nameNewMap] = res;
  std::cout << "Dictionary is created" << '\n';
}

void basko::helpCommand(std::ostream& out)
{
  out << "List of available commands" << '\n';
  out << "create [map name] - Creating a dictionary" << '\n';
  out << "add [map name][word][number] - Adding a new word to the dictionary (dictionary name, word, line number)" << '\n';
  out << "remove [map name][word] - Delete word (dictionary name, word)" << '\n';
  out << "search [map name][word] - Search (dictionary name, word)" << '\n';
  out << "show [map name] - Output (dictionary name)" << '\n';
  out << "top [map name] - Find the most common word (dictionary name)" << '\n';
  out << "merge [new map name][map name first][map name second] - Merging dictionaries" << '\n';
  out << "countwords [map name] - Output of the number of words (dictionary name)" << '\n';
  out << "clear [map name] - Clear dictionary (dictionary name)" << '\n';
  out << "matchWords [map name] - Search for words that occur in the same lines (dictionary name)" << '\n';
  out << "intersection [new map name][map name first][map name second] - Intersection of dictionaries" << '\n';
  out << "exit - Exit" << '\n';
}

bool basko::checkInt(const std::string& s)
{
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void basko::readFile(std::map< std::string, std::set< int > >& map_words, std::string filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::logic_error("File could not be opened");
  }
  int number = 1;
  std::string line;
  while (!file.eof())
  {
    std::getline(file, line);
    std::cout << number << ". " << line << '\n';
    std::stringstream stream(line);
    std::string word;
    while (stream >> word)
    {
      char c = word.back();
      if (!(c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я' || c >= '0' && c <= '9'))
      {
        word.pop_back();
      }
      map_words[word].insert(number);
    }
    number++;
  }
  file.close();
}
