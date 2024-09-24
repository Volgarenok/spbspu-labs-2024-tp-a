#include "inputdata.hpp"

#include <utility>
#include <iostream>

namespace gladyshev
{
  void processFile(std::ifstream& file, const std::string& text)
  {
    std::string word = "";
    if (file.eof())
    {
      throw std::logic_error("EMPTY FILE");
    }
    while (file >> word)
    {
      if (word == text)
      {
        break;
      }
    }
  }
}
void gladyshev::makeDict(mainDic& finres, std::ifstream& file, std::istream& in)
{
  std::streampos pos = file.tellg();
  std::string name = "";
  std::string text = "";
  in >> name >> text;
  dic result;
  std::string word = "";
  processFile(file, text);
  while (file)
  {
    if (file.get() == '\n')
    {
      break;
    }
    file >> word;
    result[word]++;
  }
  finres.insert(std::make_pair(name, result));
  file.seekg(pos);
}
void gladyshev::makeDictLen(mainDic& finres, std::ifstream& file, std::istream& in)
{
  std::streampos pos = file.tellg();
  std::string name = "";
  std::string text = "";
  size_t len = 0;
  in >> name >> text >> len;
  dic result;
  std::string word = "";
  processFile(file, text);
  while (file)
  {
    if (file.get() == '\n')
    {
      break;
    }
    file >> word;
    if (word.length() == len)
    {
      result[word]++;
    }
  }
  finres.insert(std::make_pair(name, result));
  file.seekg(pos);
}
