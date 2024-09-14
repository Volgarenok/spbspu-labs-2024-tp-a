#include "userCommands.hpp"

#include <queue>
#include <stack>
#include <stdexcept>

#include "token.hpp"

namespace rebdev
{
  class userUnary
  {
    public:
      double operator()(double x)
      {
        std::stack< token > resultStack;
        while (!queue.empty())
        {
          token top = queue.front();
          queue.pop();
          if (top.priority() == 0)
          {
            resultStack.push(top);
          }
          else if (top.priority() == 5)
          {
            resultStack.push(token{x});
          }
          else if (top.priority() == 4)
          {
            if (resultStack.size() < 1)
            {
              throw std::logic_error("Uncorrect mathematical expression!");
            }
            token first = resultStack.top();
            resultStack.pop();
            resultStack.push(top(first));
          }
          else
          {
            if (resultStack.size() < 2)
            {
              throw std::logic_error("Uncorrect mathematical expression!");
            }
            token second = resultStack.top();
            resultStack.pop();
            token first = resultStack.top();
            resultStack.pop();
            resultStack.push(top(first, second));
          }
        }
        return (resultStack.top()).getNum();
      }
      std::queue< rebdev::token > queue;
  };
  class userBinary
  {
    public:
      double operator()(double x, double y)
      {
        std::stack< token > resultStack;
        while (!queue.empty())
        {
          token top = queue.front();
          queue.pop();
          if (top.priority() == 0)
          {
            resultStack.push(top);
          }
          else if (top.priority() == 5)
          {
            resultStack.push(token{x});
          }
          else if (top.priority() == 6)
          {
            resultStack.push(token{y});
          }
          else if (top.priority() == 4)
          {
            if (resultStack.size() < 1)
            {
              throw std::logic_error("Uncorrect mathematical expression!");
            }
            token first = resultStack.top();
            resultStack.pop();
            resultStack.push(top(first));
          }
          else
          {
            if (resultStack.size() < 2)
            {
              throw std::logic_error("Uncorrect mathematical expression!");
            }
            token second = resultStack.top();
            resultStack.pop();
            token first = resultStack.top();
            resultStack.pop();
            resultStack.push(top(first, second));
          }
        }
        return (resultStack.top()).getNum();
      }
      std::queue< rebdev::token > queue;
  };
}
void rebdev::add(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
  std::queue< rebdev::token > queue;
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
      token tok(&binaryMap.at(strPart), strPart);
      if (!mathStack.empty())
      {
        token top = mathStack.top();
        mathStack.pop();
        if (top.priority() < tok.priority())
        {
          mathStack.push(top);
        }
        else
        {
          while ((top.priority() >= tok.priority()) && (top.priority() > 1))
          {
            queue.push(top);
            if (mathStack.empty())
            {
              break;
            }
            top = mathStack.top();
            mathStack.pop();
          }
        }
      }
      mathStack.push(tok);
    }
    catch (const std::out_of_range & e)
    {
      try
      {
        token tok(&unaryMap.at(strPart));
        mathStack.push(tok);
      }
      catch (const std::out_of_range & e)
      {
        if (strPart[0] == ')')
        {
          token top = mathStack.top();
          mathStack.pop();
          while (!top.leftBracket())
          {
            queue.push(top);
            top = mathStack.top();
            mathStack.pop();
          }
        }
        else if (strPart[0] == '(')
        {
          mathStack.push(token{true});
        }
        else if ((strPart[0] == 'x') || (strPart[0] == 'y'))
        {
          queue.push(token{strPart[0]});
        }
        else if ((strPart[0] == '{') || (strPart[0] == '}')){}
        else
        {
          double num = std::stod(strPart);
          queue.push(token{num});
        }
      }
    }
    lastIndex = index + 1;
  }
  while (!mathStack.empty())
  {
    queue.push(mathStack.top());
    mathStack.pop();
  }
  if (str.find(" y ") != std::string::npos)
  {
    userBinary bin;
    bin.queue = queue;
    binaryMap[name] = bin;
  }
  else
  {
    userUnary un;
    un.queue = queue;
    unaryMap[name] = un;
  }
}
void rebdev::replace(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
}
void rebdev::importFile(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
}
void rebdev::exportFile(std::string str, unary & unaryMap, binary & binaryMap, userMath & uM)
{
}
