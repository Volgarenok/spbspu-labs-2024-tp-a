#include "Commands.hpp"

#include <algorithm>
#include <fstream>

void zaparin::createDict(Dicts& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    dicts[dictname];
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
    out << (dicts.at(dictname)[word]/ dicts.at(dictname).size());
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
    dicts.at(dictname)[word]--;
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
    dicts.at(dictname).erase(word);
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
    size_t size = dicts.at(dictname).size();
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
    size_t highestRate = 0;

    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    while (it_begin != it_end)
    {
      if (it_begin->second > highestRate)
      {
        highestRate = it_begin->second;
      }

      it_begin++;
    }

    out << highestRate << "\n";
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
    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    size_t lowestRate = it_begin->second;

    while (it_begin != it_end)
    {
      if (it_begin->second < lowestRate)
      {
        lowestRate = it_begin->second;
      }

      it_begin++;
    }

    out << lowestRate << "\n";
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
    double rate = 0.0;
    size_t size = dicts.at(dictname).size();
    Dict::iterator it_begin = dicts.at(dictname).begin();
    Dict::iterator it_end = dicts.at(dictname).end();

    while (it_begin != it_end)
    {
      rate = it_begin->second / size;
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
  if (in >> dict1 >> dict2 >> result)
  {
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



std::string zaparin::filter(const std::string& word)
{
  if (word.size() == 0)
  {
    return "";
  }

  std::string newWord = word;
  char trash[9] = { '!', '?', ',', '.', '"', '\'', '-', '(', ')' };

  for (size_t i = 0; i < 9; i++)
  {
    if (trash[i] == newWord[0])
    {
      if (newWord.size() == 1)
      {
        return "";
      }
      newWord = newWord.substr(1);
    }
    if (trash[i] == newWord[newWord.size() - 1])
    {
      newWord = newWord.substr(0, newWord.size() - 1);
    }
  }

  std::transform(newWord.begin(), newWord.end(), newWord.begin(), tolower);
  return newWord;
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
    dict[filter(str)]++;
  }

  fin.close();

  return 1;
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

