#include "WorkType.hpp"
#include <stdexcept>

std::string yakshieva::getWord(std::string& str, bool ignorePoint)
{
  if (str.empty())
  {
    return "";
  }
  size_t nextSymbol;
  if (!ignorePoint)
  {
    nextSymbol = str.find_first_of(" .,()<>*&^%$#@_+=;/\\!?\n\"");
  }
  else
  {
    nextSymbol = str.find_first_of(" ,()<>*&^%$#@_+=;/\\!?\n\"");
  }
  std::string word{ "" };
  if (nextSymbol == str.npos)
  {
    word = str;
    str.erase();
  }
  else
  {
    word = str.substr(0, nextSymbol);
    str.erase(0, nextSymbol + 1);
  }
  return word;
}

size_t yakshieva::getNumber(std::string& str)
{
  if (str.empty())
  {
    return 0;
  }
  size_t lineNum;
  size_t nextSymbol;
  nextSymbol = str.find_first_of(" .,\n");
  std::string word{ "" };
  if (nextSymbol == str.npos)
  {
    word = str;
    str.erase();
  }
  else
  {
    word = str.substr(0, nextSymbol);
    str.erase(0, nextSymbol + 1);
  }
  try
  {
    lineNum = static_cast< size_t >(std::stoi(word));
  }
  catch (const std::invalid_argument&)
  {
    throw std::logic_error("<INVALID_LINE_NUMBER>");
  }
  return lineNum;
}
