#include "commands.hpp"
#include <fstream>
#include <limits>
#include "wordFreqPair.hpp"

namespace kravchenko
{
  bool isValidToSave(const std::string& name);
  bool isInvalidName(const std::string& name, const DictionaryMap& data);
  WordFreqPair toWordFreqPair(const std::pair< std::string, size_t >& p);
  void saveDict(const std::string& name, const DictionaryMap& data);
  void saveError(const std::string& name, std::ostream& out);
  bool dictWordComp(const std::pair< std::string, size_t >& lhs, const std::pair< std::string, size_t >& rhs);
  void applyOperation(FrequencyDict& out, const std::string& applyName, const DictionaryMap& data, cmd::DictOperation dictOp);
}

void kravchenko::cmdScanText(std::istream& in, std::ostream&, DictionaryMap& data)
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

void kravchenko::cmdNew(std::istream& in, std::ostream&, DictionaryMap& data)
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

void kravchenko::cmdRemove(std::istream& in, std::ostream&, DictionaryMap& data)
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
  if (data.empty())
  {
    return;
  }
  using OutputItT = std::ostream_iterator< std::string >;
  using DictPair = std::pair< std::string, FrequencyDict >;
  std::function< const std::string&(const DictPair&) > getName = &DictPair::first;
  std::transform(data.cbegin(), data.cend(), OutputItT{ out, " " }, getName);
  out << '\n';
}

bool kravchenko::isInvalidName(const std::string& name, const DictionaryMap& data)
{
  return (data.find(name) == data.cend());
}

kravchenko::WordFreqPair kravchenko::toWordFreqPair(const std::pair< std::string, size_t >& p)
{
  return WordFreqPair{ p };
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
  using outputItT = std::ostream_iterator< WordFreqPair >;
  const FrequencyDict& toSave = (*data.find(name)).second;
  std::transform(toSave.cbegin(), toSave.cend(), outputItT{ file, "\n" }, toWordFreqPair);
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
    std::function< bool(const std::string&) > pred = std::bind(isInvalidName, _1, std::cref(data));
    if (std::any_of(dictNames.cbegin(), dictNames.cend(), pred))
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
  std::string word;
  in >> dictName >> word;

  try
  {
    out << data.at(dictName).at(word) << '\n';
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kravchenko::cmdSetOperation(std::istream& in, std::ostream& out, DictionaryMap& data, cmd::DictOperation dictOp, const char* opName)
{
  std::string newDictName;
  in >> newDictName;
  if (data.find(newDictName) != data.end())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::vector< std::string > opDicts;
  while (in.peek() != '\n')
  {
    std::string name;
    in >> name;
    opDicts.push_back(name);
  }
  {
    using namespace std::placeholders;
    std::function< bool(const std::string&) > pred = std::bind(isInvalidName, _1, std::cref(data));
    if (opDicts.size() < 2 || std::any_of(opDicts.cbegin(), opDicts.cend(), pred))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  FrequencyDict operatingDict;
  dictOp(operatingDict, data.at(opDicts[0]), data.at(opDicts[1]));
  std::function< void(const std::string&) > applyOp = std::bind(applyOperation,
    std::ref(operatingDict),
    std::placeholders::_1,
    std::cref(data),
    dictOp
  );
  std::for_each(std::next(opDicts.cbegin(), 2), opDicts.cend(), applyOp);

  if (operatingDict.empty())
  {
    out << "<NO " << opName << ">\n";
  }
  data[newDictName] = operatingDict;
}

bool kravchenko::dictWordComp(const std::pair< std::string, size_t >& lhs, const std::pair< std::string, size_t >& rhs)
{
  return (lhs.first < rhs.first);
}

void kravchenko::applyOperation(FrequencyDict& out, const std::string& applyName, const DictionaryMap& data, cmd::DictOperation dictOp)
{
  FrequencyDict next;
  dictOp(next, out, data.at(applyName));
  out = next;
}

void kravchenko::cmd::dictIntersect(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs)
{
  std::set_intersection(
    lhs.cbegin(), lhs.cend(),
    rhs.cbegin(), rhs.cend(),
    std::inserter(out, out.begin()), dictWordComp
  );
}

void kravchenko::cmd::dictUnion(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs)
{
  std::set_union(
    lhs.cbegin(), lhs.cend(),
    rhs.cbegin(), rhs.cend(),
    std::inserter(out, out.begin()), dictWordComp
  );
}

void kravchenko::cmd::dictDifference(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs)
{
  std::set_difference(
    lhs.cbegin(), lhs.cend(),
    rhs.cbegin(), rhs.cend(),
    std::inserter(out, out.begin()), dictWordComp
  );
}

void kravchenko::cmd::dictComplement(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs)
{
  dictDifference(out, rhs, lhs);
}
