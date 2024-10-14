#include "Commands.hpp"

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>

#include "Additional.hpp"

void ayupov::doHelp(std::ostream& out)
{
  out << "Available commands: \n";
  out << "create <dictionary> - creates new empty <dictionary>\n";
  out << "insert <dictionary> <word> <translation> - inserts new <word> with <translation> to <dictionary>\n";
  out << "search <dictionary> <word> - prints translations of chosen <word> from <dictionary>\n";
  out << "print <dictionary> - prints <dictionary>\n";
  out << "deleteword <dictionary> <word> - deletes chosen <word> from <dictionary>\n";
  out << "deletetranslation <dictionary> <word> <translation> - deletes <translation> of the <word> from <dictionary>\n";
  out << "deletedictionary <dictionary> - deletes <dictionary>\n";
  out << "same <dictionary> <dictionary> - compares <dictionaries>\n";
  out << "merge <dictionary> <dictionary> <name> - creates a <dictionary> from the other two\n";
  out << "intersection <dictionary> <dictionary> <name> - creates a <dictionary> from the other two\n";
  out << "size <dictionary> - prints number of words in <dictionary>\n";
  out << "import <file> <dictionary> - reads data from <file> to <dictionary>\n";
  out << "export <file> <dictionary> - writes data from <dictionary> to <file>\n";
}

void ayupov::doCreate(std::map< std::string, ARDictionary>& dicts, std::istream& in)
{
  std::string newName = "";
  in >> newName;
  if (dicts.find(newName) != dicts.end())
  {
    throw std::logic_error("ALREADY EXISTS");
  }
  ARDictionary newDict;
  dicts[newName] = newDict;
}

void ayupov::doInsert(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dictionary = "";
  std::string word = "";
  std::string translation = "";
  in >> dictionary >> word >> translation;
  isDict(dicts, dictionary);
  if (!dicts.at(dictionary).insert(word, translation))
  {
    throw std::logic_error("INVALID COMMAND");
  }
}

void ayupov::doSearch(const std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictionary = "";
  std::string word = "";
  in >> dictionary >> word;
  isDict(dicts, dictionary);
  auto translation = dicts.at(dictionary).search(word);
  if (!translation)
  {
    throw std::logic_error("INAVALID COMMAND");
  }
  std::copy((*translation).begin(), (*translation).end(), std::ostream_iterator<std::string>(out, " "));
  out << "\n";
}

void ayupov::doPrint(const std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictionary = "";
  in >> dictionary;
  isDict(dicts, dictionary);
  using namespace std::placeholders;
  std::for_each(dicts.at(dictionary).dictionary.cbegin(), dicts.at(dictionary).dictionary.cend(), std::bind(printPair, std::ref(out), _1));
}

void ayupov::doDeleteWord(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dictionary = "";
  std::string word = "";
  in >> dictionary >> word;
  isDict(dicts, dictionary);
  if (!dicts.at(dictionary).remove(word))
  {
    throw std::logic_error("NO SUCH WORD");
  }
}

void ayupov::doDeleteTranslation(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dictionary = "";
  std::string word = "";
  std::string translation = "";
  in >> dictionary >> word >> translation;
  isDict(dicts, dictionary);
  if (!dicts.at(dictionary).removeTranlation(word, translation))
  {
    throw std::logic_error("INAVALID COMMAND");
  }
  if (!dicts.at(dictionary).dictionary[word].size())
  {
    dicts.at(dictionary).remove(word);
  }
}

void ayupov::doDeleteDictionary(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dictionary = "";
  in >> dictionary;
  isDict(dicts, dictionary);
  dicts.erase(dictionary);
}

void ayupov::doSame(std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out)
{
  std::string dict1 = "";
  std::string dict2 = "";
  in >> dict1 >> dict2;
  isDict(dicts, dict1);
  isDict(dicts, dict2);
  if (dicts.at(dict1) == dicts.at(dict2))
  {
    out << "<TRUE>\n";
  }
  else
  {
    out << "<FALSE>\n";
  }
}

void ayupov::doMerge(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dict1 = "";
  std::string dict2 = "";
  std::string newName = "";
  in >> dict1 >> dict2 >> newName;
  isDict(dicts, dict1);
  isDict(dicts, dict2);
  if (dicts.find(newName) != dicts.end())
  {
    throw std::logic_error("ALREADY EXISTS");
  }
  ARDictionary newDict;
  dicts[newName] = newDict;
  std::copy(dicts[dict1].dictionary.cbegin(), dicts[dict1].dictionary.cend(), std::inserter(dicts[newName].dictionary, dicts[newName].dictionary.end()));
  //...
}
