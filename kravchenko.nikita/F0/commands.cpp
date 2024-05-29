#include "commands.hpp"
#include <fstream>
#include <limits>

namespace kravchenko
{
  bool isCorrectName(const std::string& name, const DictionaryMap& data);
  bool isValidToSave(const std::string& name);
  void saveDict(const std::string& name, const DictionaryMap& data);
  void saveError(const std::string& name, std::ostream& out);
}

void kravchenko::cmdScanText(std::istream& in, DictionaryMap& data)
{
  std::string dictName;
  std::string fileName;
  in >> dictName >> fileName;

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("<INVALID FILE>");
  }

  FrequencyDict& saveDict = data[dictName];
  std::string word;
  while (file >> word)
  {
    ++saveDict[word];
  }
  file.close();
}

void kravchenko::cmdNew(std::istream& in, DictionaryMap& data)
{
  std::string dictName;
  in >> dictName;

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
  in >> dictName;

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
  std::function< const std::string&(const DictPair&) > getName = &DictPair::first;
  std::transform(data.cbegin(), data.cend(), OutputItT{ out, " " }, getName);
  out << '\n';
}

bool kravchenko::isCorrectName(const std::string& name, const DictionaryMap& data)
{
  return (data.find(name) != data.cend());
}

bool kravchenko::isValidToSave(const std::string& name)
{
  std::ofstream file(name + ".txt");
  bool isValid = file.is_open();
  file.close();
  return isValid;
}

void kravchenko::saveDict(const std::string& name, const DictionaryMap& data)
{
  std::ofstream file(name + ".txt");
  for (const auto& p : (*data.find(name)).second)
  {
    file << p.first << " : " << p.second << '\n';
  }
  file.close();
}

void kravchenko::saveError(const std::string& name, std::ostream& out)
{
  out << "<INVALID FILE FOR " << name << ">\n";
}

void kravchenko::cmdSave(std::istream& in, std::ostream& out, const DictionaryMap& data)
{
  std::vector< std::string > dictNames;
  while (in.peek() != '\n')
  {
    std::string name;
    in >> name;
    dictNames.push_back(name);
  }

  if (dictNames.empty())
  {
    dictNames.reserve(data.size());
    using DictPair = std::pair< std::string, FrequencyDict >;
    std::function< const std::string&(const DictPair&) > getName = &DictPair::first;
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

  auto partPoint = std::partition(dictNames.begin(), dictNames.end(), isValidToSave);
  std::for_each(dictNames.begin(), partPoint, std::bind(saveDict, std::placeholders::_1, std::cref(data)));
  std::for_each(partPoint, dictNames.end(), std::bind(saveError, std::placeholders::_1, std::ref(out)));
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
