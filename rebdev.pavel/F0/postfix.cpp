#include "postfix.hpp"

#include <stdexcept>
#include <stack>

void rebdev::makePostFix(std::string & str, tokQueue & queue, unary & unaryMap, binary & binaryMap, const user & userMap)
{
  size_t lastIndex = 0, index = 0;
  std::stack< token > mathStack;
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
      userMap.at(strPart)(str, unaryMap, binaryMap);
    }
    catch(const std::out_of_range & e)
    {
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
          else
          {
            double num = std::stod(strPart);
            queue.push(token{num});
          }
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
}
double rebdev::postFixToResult(tokQueue & queue)
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
    else if (top.priority() == 2)
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
