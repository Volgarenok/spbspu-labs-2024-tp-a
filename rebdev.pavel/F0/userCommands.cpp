#include "userCommands.hpp"

#include <queue>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include "token.hpp"
#include "postfix.hpp"

namespace rebdev
{
  class userOper
  {
    public:
      double operator()(double x, double y = 0)
      {
        return postFixToResult(queue, x, y);
      }
      std::queue< rebdev::token > queue;
  };
}
void rebdev::add(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
  userOper uo;
  size_t lastIndex = str.find('{'), index = 0;
  if (lastIndex == std::string::npos)
  {
    throw ("forget { in add");
  }
  std::stack< token > mathStack;
  std::string name;
  name.assign(str, (str.find("add") + 4), (lastIndex - 5));
  while (index < str.size())
  {
    index = str.find(' ', lastIndex);
    if (index == std::string::npos)
    {
      index = str.size();
    }
    std::string strPart;
    strPart.assign(str, lastIndex, (index - lastIndex));
    try
    {
      postFixBase(strPart, uo.queue, unaryMap, binaryMap, mathStack);
    }
    catch(const std::logic_error & e)
    {
      if ((strPart[0] == 'x') || (strPart[0] == 'y'))
      {
        uo.queue.push(token{strPart[0]});
      }
      else if ((strPart[0] == '{') || (strPart[0] == '}')){}
      else
      {
        throw std::logic_error("bad mathematical expression!");
      }
    }
    lastIndex = index + 1;
  }
  while (!mathStack.empty())
  {
    uo.queue.push(mathStack.top());
    mathStack.pop();
  }
  if (str.find(" y ") != std::string::npos)
  {
    binaryMap[name] = uo;
  }
  else
  {
    unaryMap[name] = uo;
  }
  uM[name] = str;
}
void rebdev::replace(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{

}
std::string getFileName(std::string str)
{
  size_t index = str.find("{ ");
  if (index == std::string::npos)
  {
    throw ("forget { in add");
  }
  std::string name;
  name.assign(str, (index + 2));
  index = name.find(' ');
  std::string fileName;
  fileName.assign(name, 0, index);
  return fileName;
}
void rebdev::importFile(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
  std::string fileName = getFileName(str);
  std::fstream inFile(fileName);
  if (!inFile.is_open())
  {
    throw std::logic_error("try to import operations from file, which doesn't exist in this catalog!");
  }
  while (!inFile.eof())
  {
    std::string inStr;
    std::getline(inFile, inStr);
    if (inStr.empty())
    {
      continue;
    }
    try
    {
      add(inStr, unaryMap, binaryMap, uM);
    }
    catch (...)
    {
      std::cerr << "uncorect operation in file: " << fileName << '\n';
    }
  }
}
void rebdev::exportFile(std::string str, userMath & uM)
{
  std::ofstream outFile(getFileName(str));
  auto begin = uM.begin();
  while (begin != uM.end())
  {
    outFile << ((*begin).second) << '\n';
    ++begin;
  }
}
