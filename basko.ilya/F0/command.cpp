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
