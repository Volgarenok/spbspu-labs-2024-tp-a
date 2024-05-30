#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <fstream>
#include "functions.hpp"

void zaparin::createDict(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    if (!dicts.count(dictname))
    {
      dicts[dictname];
    }
    else
    {
      out << "<DICTIONARY IS ALREADY EXIST>\n";
    }
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::addWord(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    dicts.at(dictname)[word]++;
  }
  else
  {
    throw std::logic_error("wrong dict name or word");
  }
}

void zaparin::getWordRate(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    out << std::fixed;
    out.precision(4);
    out << static_cast<double>(dicts.at(dictname).at(word)) / getNumOfWords(dicts.at(dictname)) << "\n";
  }
  else
  {
    throw std::logic_error("wrong dict name or word");
  }
}

void zaparin::removeWord(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    if (dicts.at(dictname).at(word) == 1)
    {
      dicts.at(dictname).erase(word);
    }
    else
    {
      dicts.at(dictname).at(word)--;
    }
  }
  else
  {
    throw std::logic_error("wrong dict name or word");
  }
}

void zaparin::deleteWord(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    if (dicts.at(dictname).count(word))
    {
      dicts.at(dictname).erase(word);
    }
    else
    {
      throw std::logic_error("no word in dict");
    }
  }
  else
  {
    throw std::logic_error("wrong dict name or word");
  }
}

void zaparin::getAllWordsRate(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    size_t size = getNumOfWords(dicts.at(dictname));

    if (size == 0)
    {
      out << "<DICTIONARY IS EMPTY>\n";
      return;
    }

    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    out << std::fixed;
    out.precision(4);
    while (it_begin != it_end)
    {
      out << it_begin->first << " " << (static_cast<double>(it_begin->second)/size) << "\n";

      it_begin++;
    }
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::getHighestRateWord(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    if (dicts.at(dictname).empty())
    {
      out << "<DICTIONARY IS EMPTY>\n";

      return;
    }

    auto maxElem = std::max_element(dicts.at(dictname).begin(), dicts.at(dictname).end(), compare);

    out << maxElem->first << "\n";
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::getLowestRateWord(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    if (dicts.at(dictname).empty())
    {
      out << "<DICTIONARY IS EMPTY>\n";

      return;
    }

    auto minElem = std::min_element(dicts.at(dictname).begin(), dicts.at(dictname).end(), compare);

    out << minElem->first << "\n";
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::getWordsWithRate(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  double leftBorder, rightBorder;
  if (in >> dictname >> leftBorder >> rightBorder)
  {
    if (leftBorder > rightBorder || leftBorder > 1 || rightBorder > 1)
    {
      throw std::logic_error("wrong borders");
    }

    if (dicts.at(dictname).empty())
    {
      out << "<DICTIONARY IS EMPTY>\n";

      return;
    }

    double rate = 0.0;
    size_t numOfWords = getNumOfWords(dicts.at(dictname));

    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    while (it_begin != it_end)
    {
      rate = static_cast<double>(it_begin->second) / numOfWords;
      if (rate >= leftBorder && rate <= rightBorder)
      {
        out << it_begin->first << "\n";
      }

      it_begin++;
    }
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::mergeDicts(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dict1, dict2, result;
  if (in >> result >> dict1 >> dict2)
  {
    if (!dicts.count(result))
    {
      throw std::logic_error("no dict in dicts");
    }

    Dict::iterator it_begin = dicts.at(dict1).begin();
    Dict::iterator it_end = dicts.at(dict1).end();

    while (it_begin != it_end)
    {
      if (dicts[result].count(it_begin->first))
      {
        dicts[result][it_begin->first] += it_begin->second;
      }
      else
      {
        dicts[result].insert({ it_begin->first, it_begin->second });
      }

      it_begin++;
    }

    it_begin = dicts.at(dict2).begin();
    it_end = dicts.at(dict2).end();

    while (it_begin != it_end)
    {
      if (dicts[result].count(it_begin->first))
      {
        dicts[result][it_begin->first] += it_begin->second;
      }
      else
      {
        dicts[result].insert({ it_begin->first, it_begin->second });
      }

      it_begin++;
    }
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::intersectDicts(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dict1, dict2;
  if (in >> dict1 >> dict2)
  {
    if (!dicts.count(dict2))
    {
      throw std::logic_error("no dict in dicts");
    }

    Dict temp;

    using namespace std::placeholders;
    std::copy_if(dicts.at(dict1).begin(), dicts.at(dict1).end(), std::inserter(temp, temp.begin()),
      std::bind(contains, dicts.at(dict2), _1));
    dicts[dict1] = temp;
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::excluseDicts(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string dict1, dict2;
  if (in >> dict1 >> dict2)
  {
    if (!dicts.count(dict2))
    {
      throw std::logic_error("no dict in dicts");
    }

    Dict temp;

    using namespace std::placeholders;
    std::copy_if(dicts.at(dict1).begin(), dicts.at(dict1).end(), std::inserter(temp, temp.begin()),
      std::bind(not_contains, dicts.at(dict2), _1));
    dicts[dict1] = temp;
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::save(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string filename;
  in >> filename;

  std::ofstream fout;
  fout.open(filename);

  if (!fout.is_open())
  {
    throw std::logic_error("Wrong filename");
  }

  Dicts::iterator it_begin = dicts.begin();
  Dicts::iterator it_end = dicts.end();

  while (it_begin != it_end)
  {
    fout << it_begin->first;

    saveDict(it_begin->second, fout);

    it_begin++;
  }
  fout << "[end]";

  fout.close();
}

void zaparin::load(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string filename, dictname;
  in >> filename;

  std::ifstream fin;
  fin.open(filename);

  if (!fin.is_open())
  {
    throw std::logic_error("Wrong filename");
  }

  while (fin >> dictname)
  {
    if (dictname == "[end]")
    {
      break;
    }
    loadDict(dicts[dictname], fin);
  }

  fin.close();
}

void zaparin::loadFile_cmd(Dicts& dicts, std::istream& in, std::ostream&)
{
  std::string filename, dictname;
  if (in >> filename >> dictname)
  {
    loadFile(dicts[dictname], filename);
  }
}

