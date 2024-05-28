#include "commands.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>

#include "calculateExpr.hpp"
#include "getInfix.hpp"
#include "infixToPostfix.hpp"

namespace zhalilov
{
  InfixToken replaceVars(const modulesMap &modules, InfixToken infToReplace);

  void checkExtraArgs(std::istream &in);

  InfixToken transformInfixWithVar(const modulesMap &modules, const InfixToken &tkn);
  std::string addDelimeterBefore(const std::string &delim, const std::string &addTo);

  std::string infixExprToString(std::list< InfixToken > infix);
  std::string varPairToString(const std::pair< std::string, std::list< InfixToken > > &pair);
  std::string modulesMapPairToString(const std::pair< std::string, varModule > &pair);

  std::string operandToString(const Operand &op);
  std::string bracketToString(const Bracket &br);
  std::string binOpToString(const BinOperator &binOp);
  std::string varExprToString(const VarExpression &varExpr);
  std::string infixTknToString(const InfixToken &tkn);
}

void zhalilov::calc(const modulesMap &modules, const std::string &filename, std::istream &in, std::ostream &out)
{
  std::list< InfixToken > infix;
  getInfix(infix, in);
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  std::list< InfixToken > infWithReplacedVars;
  using namespace std::placeholders;
  auto transformFunc = std::bind(transformInfixWithVar, std::cref(modules), _1);
  std::transform(infix.cbegin(), infix.cend(), std::back_inserter(infWithReplacedVars), transformFunc);
  std::list< PostfixToken > postfix;
  infixToPostfix(infWithReplacedVars, postfix);
  long long result = calculateExpr(postfix);
  out << result << '\n';

  std::ofstream historyFile(filename, std::ios::app);
  historyFile << infixExprToString(infWithReplacedVars);
  historyFile << " = " << result << '\n';
}

void zhalilov::modulesadd(modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  in >> moduleName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }
  checkExtraArgs(in);

  auto insertPair = modules.insert(std::make_pair(moduleName, varModule{}));
  if (!insertPair.second)
  {
    throw std::invalid_argument("module already exists");
  }
}

void zhalilov::modulesdelete(modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  in >> moduleName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }
  checkExtraArgs(in);

  if (moduleName == "main")
  {
    auto mainIt = modules.find(moduleName);
    mainIt->second.clear();
  }
  else
  {
    modules.erase(moduleName);
  }
}

void zhalilov::modulesvaradd(modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  std::string varName;
  in >> moduleName >> varName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  auto moduleIt = modules.find(moduleName);
  if (moduleIt != modules.end())
  {
    std::list< InfixToken > infix;
    getInfix(infix, in);
    if (infix.empty())
    {
      throw std::invalid_argument("not enough args");
    }
    auto varIt = moduleIt->second.find(varName);
    if (varIt != moduleIt->second.end())
    {
      varIt->second = infix;
    }
    else
    {
      moduleIt->second.insert(std::make_pair(varName, infix));
    }
  }
  else
  {
    throw std::invalid_argument("module doesn't exist");
  }
}

void zhalilov::modulesvardelete(modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  std::string varName;
  in >> moduleName >> varName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }
  checkExtraArgs(in);

  auto moduleIt = modules.find(moduleName);
  if (moduleIt != modules.end())
  {
    moduleIt->second.erase(varName);
  }
  else
  {
    throw std::invalid_argument("module doesn't exist");
  }
}

void zhalilov::modulesshow(const modulesMap &modules, std::istream &in, std::ostream &out)
{
  checkExtraArgs(in);

  std::string toOutput;
  std::list< std::string > modulesStrings;
  auto it = modules.cbegin();
  out << modulesMapPairToString(*(it++));
  std::transform(it, modules.cend(), std::back_inserter(modulesStrings), modulesMapPairToString);
  auto func = std::bind(addDelimeterBefore, std::string("\n"), std::placeholders::_1);
  std::transform(modulesStrings.cbegin(), modulesStrings.cend(), modulesStrings.begin(), func);
  out << std::accumulate(modulesStrings.cbegin(), modulesStrings.cend(), std::string("")) << '\n';
}

void zhalilov::modulesimport(modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  std::string fileName;
  in >> moduleName >> fileName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }
  checkExtraArgs(in);

  std::ifstream file(fileName);
  if (!file)
  {
    throw std::invalid_argument("bad filename");
  }

  varModule imported;
  while (!file.eof())
  {
    std::string name;
    file >> name;
    std::list< InfixToken > infix;
    getInfix(infix, file);
    imported.insert(std::make_pair(name, infix));
  }
  modules.erase(moduleName);
  modules.insert(std::make_pair(moduleName, imported));
}

void zhalilov::modulesexport(const modulesMap &modules, std::istream &in, std::ostream &)
{
  std::string moduleName;
  std::string fileName;
  in >> moduleName >> fileName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }
  checkExtraArgs(in);

  auto module = modules.find(moduleName);
  if (module == modules.end())
  {
    throw std::invalid_argument("module doesn't exist");
  }

  std::ofstream file(fileName);
  for (auto it = module->second.cbegin(); it != module->second.cend(); ++it)
  {
    file << it->first << ' ';
    file << infixExprToString(it->second);
  }
}

void zhalilov::historyshow(const std::string &filename, std::istream &in, std::ostream &out)
{
  checkExtraArgs(in);

  std::ifstream file(filename);
  std::list< std::string > history;
  while (!file.eof())
  {
    std::string temp;
    std::getline(file, temp);
    history.push_back(temp);
  }
  history.pop_back();
  while (!history.empty())
  {
    out << history.back() << '\n';
    history.pop_back();
  }
}

void zhalilov::historyclear(const std::string &filename, std::istream &in, std::ostream &)
{
  checkExtraArgs(in);
  std::ifstream file(filename, std::ios::out | std::ios::trunc);
}

zhalilov::InfixToken zhalilov::replaceVars(const modulesMap &modules, InfixToken infToReplace)
{
  std::string moduleName = infToReplace.getVarExpression().getModuleName();
  std::string varName = infToReplace.getVarExpression().gerVarName();
  varModule module;
  std::list< InfixToken > varList;
  try
  {
    module = modules.at(moduleName);
    varList = module.at(varName);
  }
  catch (const std::out_of_range &e)
  {
    throw std::invalid_argument("incorrect args");
  }
  std::list< InfixToken > replaced;
  std::list< long long > args = infToReplace.getVarExpression().getArgs();
  for (auto exprIt = varList.cbegin(); exprIt != varList.cend(); ++exprIt)
  {
    if (exprIt->getType() == PrimaryType::VarExpression)
    {
      if (args.empty())
      {
        throw std::invalid_argument("not enough args");
      }
      replaced.push_back(InfixToken(Operand(args.front())));
      args.pop_front();
    }
    else
    {
      replaced.push_back(*exprIt);
    }
  }
  std::list< PostfixToken > postfixReplaced;
  infixToPostfix(replaced, postfixReplaced);
  long long calculated = calculateExpr(postfixReplaced);
  return InfixToken(Operand(calculated));
}

void zhalilov::checkExtraArgs(std::istream &in)
{
  std::string checkStream;
  std::getline(in, checkStream);
  if (!checkStream.empty())
  {
    throw std::invalid_argument("too many args");
  }
}

std::string zhalilov::infixExprToString(std::list< InfixToken > infix)
{
  std::string toReturn;
  if (!infix.empty())
  {
    auto it = infix.cbegin();
    toReturn = infixTknToString(*(it++));
    std::list< std::string > tknStrings;
    std::transform(it, infix.cend(), std::back_inserter(tknStrings), infixTknToString);
    std::list< std::string > withDelim;
    auto addDelim = std::bind(addDelimeterBefore, " ", std::placeholders::_1);
    std::transform(tknStrings.cbegin(), tknStrings.cend(), std::back_inserter(withDelim), addDelim);
    toReturn += std::accumulate(withDelim.cbegin(), withDelim.cend(), std::string(""));
  }
  return toReturn;
}

std::string zhalilov::varPairToString(const std::pair< std::string, std::list< InfixToken > > &pair)
{
  std::string toReturn = pair.first + " = ";
  toReturn += infixExprToString(pair.second);
  return toReturn;
}

std::string zhalilov::modulesMapPairToString(const std::pair< std::string, varModule > &pair)
{
  std::string toReturn = pair.first + ":";
  if (!pair.second.empty())
  {
    std::list< std::string > varStrings;
    std::transform(pair.second.cbegin(), pair.second.cend(), std::back_inserter(varStrings), varPairToString);
    auto func = std::bind(addDelimeterBefore, std::string("\n"), std::placeholders::_1);
    std::transform(varStrings.cbegin(), varStrings.cend(), varStrings.begin(), func);
    toReturn += std::accumulate(varStrings.cbegin(), varStrings.cend(), std::string(""));
  }
  else
  {
    toReturn += "\nNo vars saved :/";
  }
  return toReturn;
}

zhalilov::InfixToken zhalilov::transformInfixWithVar(const modulesMap &modules, const InfixToken &tkn)
{
  if (tkn.getType() == PrimaryType::VarExpression)
  {
    return (replaceVars(modules, tkn));
  }
  return tkn;
}

std::string zhalilov::addDelimeterBefore(const std::string &delim, const std::string &addTo)
{
  return delim + addTo;
}

std::string zhalilov::operandToString(const Operand &op)
{
  return std::to_string(op.getNum());
}

std::string zhalilov::bracketToString(const Bracket &br)
{
  if (br.getType() == PrimaryType::CloseBracket)
  {
    return "(";
  }
  return ")";
}

std::string zhalilov::binOpToString(const BinOperator &binOp)
{
  switch (binOp.getType())
  {
  case BinOperator::Type::Addition:
    return "+";
  case BinOperator::Type::Subtraction:
    return "-";
  case BinOperator::Type::Multiplication:
    return "*";
  case BinOperator::Type::Division:
    return "/";
  case BinOperator::Type::Mod:
    return "%";
  default:
    return "";
  }
}

std::string zhalilov::varExprToString(const VarExpression &varExpr)
{
  std::string toReturn = varExpr.gerVarName();
  std::list< long long > args = varExpr.getArgs();
  if (!args.empty())
  {
    auto it = args.cbegin();
    toReturn += '(' + std::to_string(*it);
    ++it;
    std::list< std::string > argsInString;
    std::transform(it, args.cend(), std::back_inserter(argsInString), static_cast< std::string(*)(long long) >(std::to_string));
    auto addDelim = std::bind(addDelimeterBefore, ", ", std::placeholders::_1);
    std::transform(argsInString.cbegin(), argsInString.cend(), argsInString.begin(), addDelim);
    toReturn += std::accumulate(argsInString.cbegin(), argsInString.cend(), std::string(""));
    toReturn += ')';
  }
  return toReturn;
}

std::string zhalilov::infixTknToString(const InfixToken &tkn)
{
  switch (tkn.getType())
  {
  case PrimaryType::Operand:
    return operandToString(tkn.getOperand());
    break;
  case PrimaryType::BinOperator:
    return binOpToString(tkn.getBinOperator());
    break;
  case PrimaryType::VarExpression:
    return varExprToString(tkn.getVarExpression());
    break;
  default:
    return bracketToString(tkn.getBracket());
    break;
  }
}
