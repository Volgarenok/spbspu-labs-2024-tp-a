#include "Commands.hpp"

#include <fstream>
#include "Delimeter.hpp"

void zaparin::createDict(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  
  if (in >> dictname)
  {
    std::map< std::string, HashTable>::iterator it_begin = dicts.begin();
    std::map< std::string, HashTable>::iterator it_end = dicts.end();

    while (it_begin != it_end)
    {
      if (it_begin->first == dictname)
      {
        throw std::logic_error("Dict is already exsist\n");
      }
      it_begin++;
    }

    dicts[dictname] = HashTable();
  }
}

void zaparin::addWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    dicts.at(dictname).insert(word);
  }
}

void zaparin::getWordRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    dicts.at(dictname).getWordRate(word);
  }
}

void zaparin::removeWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    dicts.at(dictname).removeWord(word);
  }
}

void zaparin::deleteWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname, word;
  if (in >> dictname >> word)
  {
    dicts.at(dictname).deleteWord(word);
  }
}

void zaparin::getAllWordsRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    dicts.at(dictname).print(out);
  }
}

void zaparin::getHighestRateWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    out << dicts.at(dictname).getHighestRateWord() << "\n";
  }
}

void zaparin::getLowestRateWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    out << dicts.at(dictname).getLowestRateWord() << "\n";
  }
}

void zaparin::getWordsWithRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  double leftBorder, rightBorder;
  if (in >> dictname >> leftBorder >> rightBorder)
  {
    dicts.at(dictname).getWordsWithRate(leftBorder, rightBorder);
  }
}

void zaparin::getThreeHighestRateWords(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname;
  if (in >> dictname)
  {
    dicts.at(dictname).getThreeHighestRateWords();
  }
}

void zaparin::mergeDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string newdictname, dictname1, dictname2;

  in >> newdictname >> dictname1 >> dictname2;

  dicts[newdictname] = HashTable();

  dicts.at(newdictname).mergeDicts(dicts.at(dictname1), dicts.at(dictname2));
}

void zaparin::intersectDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname1, dictname2;
  if (in >> dictname1 >> dictname2)
  {
    dicts.at(dictname1).intersectDicts(dicts.at(dictname2));
  }
}

void zaparin::excluseDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictname1, dictname2;
  if (in >> dictname1 >> dictname2)
  {
    dicts.at(dictname1).excluseDicts(dicts.at(dictname2));
  }
}

void zaparin::loadFile(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string filename, dictname;
  if (in >> filename >> dictname)
  {
    dicts[dictname] = HashTable();

    std::ifstream fin;
    fin.open(filename);

    if (!fin.is_open())
    {
      throw std::logic_error("file is not opened\n");
    }

    std::string str;
    while (fin >> str)
    {
      dicts.at(dictname).insert(str);
    }

    fin.close();
  }
}

void zaparin::save(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
{
  std::string filename;
  in >> filename;

  std::ofstream fout;
  fout.open(filename);

  if (!fout.is_open())
  {
    throw std::logic_error("Wrong filename");
  }

  std::map< std::string, zaparin::HashTable >::iterator it_begin = dicts.begin();
  std::map< std::string, zaparin::HashTable >::iterator it_end = dicts.end();

  while (it_begin != it_end)
  {
    fout << it_begin->first;
    it_begin->second.save(fout);

    it_begin++;
  }
  fout << "[end]";

  fout.close();
}

void zaparin::load(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out)
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
    dicts[dictname].load(fin);
  }

  fin.close();
}
