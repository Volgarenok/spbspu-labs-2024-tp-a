#include "commands.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <vector>
#include "dictWord.hpp"

namespace kravchenko
{
  bool isCorrectName(const std::string& name, const DictionaryMap& data);
}

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

bool kravchenko::isCorrectName(const std::string& name, const DictionaryMap& data)
{
  return (data.find(name) != data.cend());
}

void kravchenko::cmdSave(std::istream& in, std::ostream& out, const DictionaryMap& data)
{
  std::vector< std::string > dictNames;
  {
    using InputItT = std::istream_iterator< std::string >;
    std::copy(InputItT{ in }, InputItT{}, std::back_inserter(dictNames));
  }

  if (dictNames.empty())
  {
    using DictPair = std::pair< std::string, FrequencyDict >;
    std::function< std::string(const DictPair&) > getName = &DictPair::first;
    std::transform(data.cbegin(), data.cend(), std::back_inserter(dictNames), getName);
  }
  else
  {
    using namespace std::placeholders;
    std::function< bool(const std::string&) > pred = std::bind(isCorrectName, _1, std::cref(data));
    if (!(std::all_of(dictNames.cbegin(), dictNames.cend(), pred)))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  for (const std::string& name : dictNames)
  {
    std::ofstream file(name + ".txt");
    if (!file.is_open())
    {
      out << "<INVALID FILE FOR " + name + ">\n";
      continue;
    }
    for (const auto& p : data.at(name))
    {
      file << p.first << " : " << p.second << '\n';
    }
    file.close();
  }
}

void kravchenko::cmdFreq(std::istream& in, std::ostream& out, const DictionaryMap& data, const cmd::FreqArgs& args)
{
  std::string arg;
  in >> arg;
  try
  {
    args.at(arg)(in, out, data);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kravchenko::cmd::freqWord(std::istream& in, std::ostream& out, const DictionaryMap& data)
{
  std::string dictName;
  in >> dictName;

  std::string word;
  in >> word;

  try
  {
    out << data.at(dictName).at(word) << '\n';
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}
