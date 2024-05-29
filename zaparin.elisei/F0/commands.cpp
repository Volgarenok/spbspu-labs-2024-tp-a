#include "commands.hpp"

#include <algorithm>
#include <fstream>

std::string zaparin::filter(std::string word)
{
  if (word.size() == 0)
  {
    return "";
  }

  char trash[9] = { '!', '?', ',', '.', '"', '\'', '-', '(', ')' };

  for (size_t i = 0; i < 9; i++)
  {
    if (trash[i] == word[0])
    {
      if (word.size() == 1)
      {
        return "";
      }
      word = word.substr(1);
    }
    if (trash[i] == word[word.size() - 1])
    {
      word = word.substr(0, word.size() - 1);
      break;
    }
  }

  std::transform(word.begin(), word.end(), word.begin(), tolower);
  return word;
}

bool zaparin::loadFile(Dict& dict, std::string& filename)
{
  std::ifstream fin;
  fin.open(filename);

  if (!fin.is_open())
  {
    throw std::logic_error("file is not opened\n");
  }

  std::string str;
  while (fin >> str)
  {
    str = filter(str);
    if (str != "")
    {
      dict[str]++;
    }
  }

  fin.close();

  return 1;
}

size_t zaparin::getNumOfWords(Dict& dict)
{
  size_t numOfWords = 0;

  Dict::iterator it_begin = dict.begin();
  Dict::iterator it_end = dict.end();

  while (it_begin != it_end)
  {
    numOfWords += it_begin->second;

    it_begin++;
  }

  return numOfWords;
}

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

void zaparin::addWord(Dicts& dicts, std::istream& in, std::ostream& out)
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
    out << ((double)dicts.at(dictname).at(word)/getNumOfWords(dicts.at(dictname))) << "\n";
  }
  else
  {
    throw std::logic_error("wrong dict name or word");
  }
}

void zaparin::removeWord(Dicts& dicts, std::istream& in, std::ostream& out)
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

void zaparin::deleteWord(Dicts& dicts, std::istream& in, std::ostream& out)
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
      out << it_begin->first << " " << ((double)it_begin->second/size) << "\n";

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

    size_t highestRate = 0;
    std::string word;

    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    while (it_begin != it_end)
    {
      if (it_begin->second > highestRate)
      {
        word = it_begin->first;
        highestRate = it_begin->second;
      }

      it_begin++;
    }

    out << word << "\n";
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

    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    std::string word;
    size_t lowestRate = it_begin->second;

    while (it_begin != it_end)
    {
      if (it_begin->second < lowestRate)
      {
        word = it_begin->first;
        lowestRate = it_begin->second;
      }

      it_begin++;
    }

    out << word << "\n";
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
      rate = (double)it_begin->second / numOfWords;
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

void zaparin::mergeDicts(Dicts& dicts, std::istream& in, std::ostream& out)
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

void zaparin::intersectDicts(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dict1, dict2;
  if (in >> dict1 >> dict2)
  {
    if (!dicts.count(dict2))
    {
      throw std::logic_error("no dict in dicts");
    }

    Dict temp;

    Dict::iterator it_begin = dicts.at(dict1).begin();
    Dict::iterator it_end = dicts.at(dict1).end();

    while (it_begin != it_end)
    {
      if (dicts[dict2].count(it_begin->first))
      {
        temp.insert({ it_begin->first, it_begin->second });
      }
      it_begin++;
    }

    dicts[dict1] = temp;
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::excluseDicts(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dict1, dict2;
  if (in >> dict1 >> dict2)
  {
    if (!dicts.count(dict2))
    {
      throw std::logic_error("no dict in dicts");
    }

    Dict temp;

    Dict::iterator it_begin = dicts.at(dict1).begin();
    Dict::iterator it_end = dicts.at(dict1).end();

    while (it_begin != it_end)
    {
      if (!dicts[dict2].count(it_begin->first))
      {
        temp.insert({ it_begin->first, it_begin->second });
      }
      it_begin++;
    }

    dicts[dict1] = temp;
  }
  else
  {
    throw std::logic_error("wrong dict name");
  }
}

void zaparin::saveDict(Dict& dict, std::ostream& out)
{
  Dict::iterator it_begin = dict.begin();
  Dict::iterator it_end = dict.end();

  while (it_begin != it_end)
  {
    out << " " << it_begin->first << " " << it_begin->second;

    it_begin++;
  }
  out << "\n";
}

void zaparin::save(Dicts& dicts, std::istream& in, std::ostream& out)
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

void zaparin::loadDict(Dict& dict, std::istream& in)
{
  std::string word;
  size_t numOfWords;

  while (in.peek() != '\n')
  {
    in >> word >> numOfWords;

    dict.insert({ word, numOfWords });
  }
}

void zaparin::load(Dicts& dicts, std::istream& in, std::ostream& out)
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

void zaparin::loadFile_cmd(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string filename, dictname;
  if (in >> filename >> dictname)
  {
    loadFile(dicts[dictname], filename);
  }
}

