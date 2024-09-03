#include "postfix.hpp"

#include <stdexcept>
#include <stack>

void rebdev::makePostFix(std::string & str, std::queue< token > & queue)
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
    if (((strPart.size()) == 1) && (!isdigit(strPart[0])))
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
        mathStack.push(token{strPart[0]});
      }
      else
      {
        token operTok(strPart[0]);
        if (!mathStack.empty())
        {
          token top = mathStack.top();
          mathStack.pop();
          if (top.priority() < operTok.priority())
          {
            mathStack.push(top);
          }
          else
          {
            while (top.priority() >= operTok.priority())
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
        mathStack.push(operTok);
      }
    }
    else if (strPart.size() >= 1)
    {
      queue.push(token{std::stoll(strPart)});
    }

    lastIndex = index + 1;
  }
  while (!mathStack.empty())
  {
    queue.push(mathStack.top());
    mathStack.pop();
  }
}
long long rebdev::postFixToResult(std::queue< token > & queue)
{
  std::stack< token > resultStack;
  while (!queue.empty())
  {
    token top = queue.front();
    queue.pop();
    if (!top.isNum())
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
    else
    {
      resultStack.push(top);
    }
  }
  return (resultStack.top()).getNum();
}
