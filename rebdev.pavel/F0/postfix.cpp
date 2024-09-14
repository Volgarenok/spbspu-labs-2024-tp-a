#include "postfix.hpp"

#include <stdexcept>
#include <stack>

void rebdev::makePostFix(std::string & str, tokQueue & queue, unary & un, binary & bin, const user & usr, userMath & uM)
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
      usr.at(strPart)(str, un, bin, uM);
      index = str.find('}');
      if (index == std::string::npos)
      {
        throw ("forget } in add");
      }
      ++index;
    }
    catch(const std::out_of_range & e)
    {
      try
      {
        token tok(&bin.at(strPart), strPart);
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
            while ((top.priority() >= tok.priority()) && (top.priority() > 2))
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
          token tok(&un.at(strPart));
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
            try
            {
              double num = std::stod(strPart);
              queue.push(token{num});
            }
            catch (const std::exception & e)
            {
              throw std::logic_error("bad mathematical expression!");
            }
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
    else
    {
      token first = resultStack.top();
      resultStack.pop();
      if (top.priority() != 4)
      {
        token second = resultStack.top();
        resultStack.pop();
        resultStack.push(top(second, first));
      }
      else
      {
        resultStack.push(top(first));
      }
    }
  }
  return (resultStack.top()).getNum();
}
