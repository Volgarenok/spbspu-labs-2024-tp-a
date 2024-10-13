#include "SupportCmds.hpp"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include "DictionaryLineIO.hpp"

std::pair< std::string, size_t > getPairWithTotalFrequency(const sazanov::DictionaryLineI& line, sazanov::FrequencyDictionary& dict)
{
  return {line.pair.first, line.pair.second + dict[line.pair.first]};
}

void sazanov::readDict(const std::string& dictName, const std::string& fileName, DictionaryCollection& dictionaries)
{
  std::fstream file(fileName);
  FrequencyDictionary temp;
  FrequencyDictionary& dict = dictionaries[dictName];
  using namespace std::placeholders;
  using inputIt = std::istream_iterator< DictionaryLineI >;
  std::transform(inputIt{file}, inputIt{}, std::inserter(temp, temp.begin()), std::bind(getPairWithTotalFrequency, _1, std::ref(dict)));
  std::copy(dict.begin(), dict.end(), std::inserter(temp, temp.begin()));
  dict = std::move(temp);
}

bool sazanov::isCorrectFile(const std::string& fileName)
{
  std::ifstream file(fileName);
  DictionaryLineI checked;
  while (!file.eof())
  {
    file >> checked;
  }
  return static_cast< bool >(file);
}
