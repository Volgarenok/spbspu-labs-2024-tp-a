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
