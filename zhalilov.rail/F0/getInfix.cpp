#include "getInfix.hpp"

#include <string>
#include <istream>

namespace zhalilov
{
  bool isBracket(char symb)
  {
    if (symb == '(' || symb == ')')
    {
      return true;
    }
    return false;
  }

  bool isBinaryOp(char symb)
  {
    bool isOp = symb == '+' || symb == '-';
    isOp = isOp || symb == '/' || symb == '*';
    isOp = isOp || symb == '%';
    return isOp;
  }

  size_t processVarExpr(const std::string &toProcess, VarExpression &varExpr, size_t &newIndex)
  {
    std::string moduleName = "main";
    size_t i = 0;
    bool isVarExpr = false;
    while (std::isalpha(toProcess[i]))
    {
      i++;
    }
    if (i != 0)
    {
      std::string varName;
      if (toProcess[i] == ':')
      {
        moduleName = toProcess.substr(0, i);
        size_t nameStartPos = ++i;
        while (std::isalpha(toProcess[i]))
        {
          i++;
        }
        if (nameStartPos != i)
        {
          varName = toProcess.substr(nameStartPos, i - nameStartPos);
        }
      }
      else
      {
        varName = toProcess.substr(0, i);
      }
      std::list< long long > args;
      if (toProcess[i] == '(')
      {
        i++;
        while (toProcess[i] != ')')
        {
          if (toProcess.size() == i)
          {
            throw std::invalid_argument("getInfix.cpp: toProcess.size() == i");
          }
          if (toProcess[i] != ',')
          {
            size_t tmp = 0;
            args.push_back(std::stoll(toProcess.substr(i), &tmp));
            i += tmp;
          }
          else
          {
            i++;
          }
        }
      }
      varExpr = VarExpression(moduleName, varName, args);
      isVarExpr = true;
    }
    newIndex = i;
    return isVarExpr;
  }
}

void zhalilov::getInfix(std::list< InfixToken > &list, std::istream &in)
{
  std::string str;
  std::getline(in, str);
  size_t i = 0;
  size_t tmp = 0;
  long long number = 0;
  while (i < str.size())
  {
    if (!std::isspace(str[i]))
    {
      try
      {
        number = std::stoll(str.substr(i), &tmp);
        list.emplace_back(InfixToken(Operand(number)));
        i += tmp;
      }
      catch (...)
      {
        if (isBracket(str[i]))
        {
          list.emplace_back(InfixToken(Bracket(str[i])));
        }
        else if (isBinaryOp(str[i]))
        {
          list.emplace_back(InfixToken(BinOperator(str[i])));
        }
        else
        {
          VarExpression varExpr;
          size_t newIndex = 0;
          if (processVarExpr(str.substr(i), varExpr, newIndex))
          {
            list.emplace_back(InfixToken(VarExpression(varExpr)));
            i += newIndex;
          }
          else
          {
            throw std::invalid_argument("getInfix.cpp: processVarExpr == false");
          }
        }
      }
    }
    i++;
  }
}
