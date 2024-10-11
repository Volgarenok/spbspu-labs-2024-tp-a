#include "Additional.hpp"

#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iostream>

void ayupov::isDict(const std::map< std::string, ARDictionary >& dicts, const std::string& dict)
{
  if (dicts.find(dict) == dicts.end())
  {
    throw std::logic_error("NO SUCH DICTIONARY");
  }
}

void ayupov::printDict(std::ostream& out, const std::pair< const std::string, ARDictionary >& dict)
{
	std::for_each(dict.second.dictionary.begin(), dict.second.dictionary.end(), std::bind(printPair, std::ref(out), std::placeholders::_1));
}

void ayupov::printPair(std::ostream& out, const std::pair< std::string, std::set<std::string> >& pair)
{
	out << pair.first << ": ";
	std::for_each(pair.second.begin(), pair.second.end(), std::bind(printWord, std::ref(out), std::placeholders::_1));
	out << "\n";
}

void ayupov::printWord(std::ostream& out, const std::string& word)
{
	out << word << " ";
}
