#include "dictionaryIO.hpp"

#include <algorithm>
#include <iterator>

std::ostream& chernikova::operator<<(std::ostream& output, TranslationsO&& obj)
{
  std::copy(obj.set.begin(), obj.set.end(), std::ostream_iterator< std::string >(output, " "));
  return output;
}

std::ostream& chernikova::operator<<(std::ostream& output, DictionaryLineO&& obj)
{
  output << obj.pair.first << " : ";
  output << TranslationsO{ obj.pair.second };
  output << "\n";
  return output;
}

std::ostream& chernikova::operator<<(std::ostream& output, const DictionaryLineO& obj)
{
  output << DictionaryLineO{ obj.pair };
  return output;
}

chernikova::DictionaryLineO chernikova::toDictionaryLineO(const std::pair< std::string, std::set< std::string > >& pair)
{
  return DictionaryLineO{ pair };
}

std::ostream& chernikova::operator<<(std::ostream& output, DictionaryO&& obj)
{
  std::transform(obj.hashTable.begin(), obj.hashTable.end(), std::ostream_iterator< DictionaryLineO >(output), toDictionaryLineO);
  return output;
}
