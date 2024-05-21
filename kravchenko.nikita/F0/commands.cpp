#include "commands.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <utility>
#include "dictWord.hpp"

void kravchenko::cmdScanText(std::istream& in, DictionaryMap& data)
{
  std::string dictName;
  in >> dictName;

  std::string fileName;
  in >> fileName;

  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("<INVALID FILE>");
  }

  FrequencyDict& saveDict = data[dictName];
  while (!file.eof())
  {
    std::string word;
    if (file >> DictWord{ word })
    {
      ++saveDict[word];
    }
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), ' ');
  }
  file.close();
}

void kravchenko::cmdNew(std::istream& in, DictionaryMap& data)
{
  std::string dictName;
  if (!(in >> dictName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if (data.find(dictName) == data.cend())
  {
    data[dictName];
  }
  else
  {
    throw std::invalid_argument("<EXIST>");
  }
}

void kravchenko::cmdRemove(std::istream& in, DictionaryMap& data)
{
  std::string dictName;
  if (!(in >> dictName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  auto rmIt = data.find(dictName);
  if (rmIt != data.end())
  {
    data.erase(rmIt);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kravchenko::cmdList(std::ostream& out, const DictionaryMap& data)
{
  using OutputItT = std::ostream_iterator< std::string >;
  using DictPair = std::pair< std::string, FrequencyDict >;
  std::function< std::string(const DictPair&) > getName = &DictPair::first;
  std::transform(data.cbegin(), data.cend(), OutputItT{ out, " " }, getName);
  out << '\n';
}
