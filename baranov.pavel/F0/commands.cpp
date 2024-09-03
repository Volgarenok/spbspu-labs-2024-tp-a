#include "commands.hpp"
#include <fstream>
#include <algorithm>
#include <functional>
#include "commandsImpl.hpp"

void baranov::createCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("Already exists\n");
  }
  dicts[dictName];
  if (in.peek() != '\n')
  {
    std::string fileName;
    in >> fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::logic_error("Invalid file name\n");
    }
    extendDict(dicts[dictName], file);
  }
}

void baranov::clearCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  dicts.at(dictName).clear();
}

void baranov::deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dicts.erase(it);
}

void baranov::addWordsCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  std::string fileName;
  in >> fileName;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("Invalid file name\n");
  }
  extendDict(dicts[dictName], file);
}

void baranov::printCountCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  if (in.peek() != '\n')
  {
    std::string dictName;
    in >> dictName;
    out << getWordCount(dicts.at(dictName), word) << '\n';
  }
  else
  {
    if (dicts.empty())
    {
      throw std::logic_error("There are no dictionaries\n");
    }
    std::map< std::string, size_t > counts;
    using namespace std::placeholders;
    auto countFunc = std::bind(getCount, _1, word);
    std::transform(dicts.cbegin(), dicts.cend(), std::inserter(counts, counts.begin()), countFunc);
    auto outFunc = std::bind(printElement, _1, std::ref(out));
    std::for_each(counts.cbegin(), counts.cend(), outFunc);
  }
}

void baranov::printDictCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  const dict_t & dict = dicts.at(dictName);
  using namespace std::placeholders;
  auto outFunc = std::bind(printElement, _1, std::ref(out));
  std::for_each(dict.cbegin(), dict.cend(), outFunc);
}

void baranov::printTopCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  dict_t tempdict = dicts.at(dictName);
  size_t tmp = 0;
  if (in.peek() != '\n')
  {
    in >> tmp;
    if (tmp == 0)
    {
      throw std::logic_error("Invalid command\n");
    }
  }
  size_t count = tmp == 0 ? tempdict.size() : std::min(tmp, tempdict.size());
  if (count == 0)
  {
    return;
  }
  for (size_t i = 0; i < count; ++i)
  {
    auto max = std::max_element(tempdict.cbegin(), tempdict.cend(), countComparator);
    printElement(*max, out);
    tempdict.erase(max);
  }
}

void baranov::joinCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  in >> dict1Name;
  const dict_t & dict1 = dicts.at(dict1Name);
  std::string dict2Name;
  in >> dict2Name;
  const dict_t & dict2 = dicts.at(dict2Name);
  dict_t result = dict1;
  using namespace std::placeholders;
  auto join = std::bind(joinWord, _1, std::ref(result));
  std::for_each(dict2.cbegin(), dict2.cend(), join);
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::intersectCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  in >> dict1Name;
  const dict_t & dict1 = dicts.at(dict1Name);
  std::string dict2Name;
  in >> dict2Name;
  const dict_t & dict2 = dicts.at(dict2Name);
  dict_t common;
  using namespace std::placeholders;
  auto predicate = std::bind(isContains, std::ref(dict2), _1);
  std::copy_if(dict1.cbegin(), dict1.cend(), std::inserter(common, common.begin()), predicate);
  dict_t result;
  auto addCounts = std::bind(addWordCount, _1, std::cref(dict2));
  std::transform(common.begin(), common.end(), std::inserter(result, result.begin()), addCounts);
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::saveCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  std::string fileName;
  in >> fileName;
  std::ofstream file(fileName);
  file << dictName << '\n';
  const dict_t & dict = dicts.at(dictName);
  using namespace std::placeholders;
  auto outFunc = std::bind(printElement, _1, std::ref(file));
  std::for_each(dict.cbegin(), dict.cend(), outFunc);
}

void baranov::lsDictsCmd(const std::map< std::string, dict_t > & dicts, std::istream &, std::ostream & out)
{
  using namespace std::placeholders;
  auto outFunc = std::bind(printDictName, _1, std::ref(out));
  std::for_each(dicts.cbegin(), dicts.cend(), outFunc);
}

