#include "commands.hpp"

#include <fstream>
#include <iostream>
#include <list>

#include "calculateExpr.hpp"
#include "getInfix.hpp"
#include "infixToPostfix.hpp"

namespace zhalilov
{
  InfixToken replaceVars(const modulesMap &modules, InfixToken infToReplace);
  void outputInfix(std::list< InfixToken > infix, std::ostream &out);
  void checkExtraArgs(std::istream &in);
  std::ostream &coutOperand(std::ostream &out, const Operand &op);
  std::ostream &coutBracket(std::ostream &out, const Bracket &br);
  std::ostream &coutBinOp(std::ostream &out, const BinOperator &binOp);
  std::ostream &coutVarExpr(std::ostream &out, const VarExpression &varExpr);
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
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    if (it->getType() == PrimaryType::VarExpression)
    {
      infWithReplacedVars.push_back(replaceVars(modules, *it));
    }
    else
    {
      infWithReplacedVars.push_back(*it);
    }
  }
  std::list< PostfixToken > postfix;
  infixToPostfix(infWithReplacedVars, postfix);
  long long result = calculateExpr(postfix);
  out << result << '\n';

  std::ofstream historyFile(filename, std::ios::app);
  outputInfix(infWithReplacedVars, historyFile);
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

  for (auto it = modules.cbegin(); it != modules.cend(); ++it)
  {
    out << it->first << ":\n";
    if (!it->second.empty())
    {
      for (auto inModuleIt = it->second.cbegin(); inModuleIt != it->second.cend(); ++inModuleIt)
      {
        if (inModuleIt != it->second.cbegin())
        {
          out << '\n';
        }
        out << inModuleIt->first << " = ";
        outputInfix(inModuleIt->second, out);
      }
    }
    else
    {
      out << "No vars saved :/";
    }
    out << '\n';
  }
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
    outputInfix(it->second, file);
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

void zhalilov::outputInfix(std::list< InfixToken > infix, std::ostream &out)
{
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    if (it != infix.begin())
    {
      out << ' ';
    }
    switch (it->getType())
    {
    case PrimaryType::Operand:
      coutOperand(out, it->getOperand());
      break;
    case PrimaryType::BinOperator:
      coutBinOp(out, it->getBinOperator());
      break;
    case PrimaryType::VarExpression:
      coutVarExpr(out, it->getVarExpression());
      break;
    default:
      coutBracket(out, it->getBracket());
      break;
    }
  }
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

std::ostream &zhalilov::coutOperand(std::ostream &out, const Operand &op)
{
  return out << op.getNum();
}

std::ostream &zhalilov::coutBracket(std::ostream &out, const Bracket &br)
{
  if (br.getType() == PrimaryType::CloseBracket)
  {
    return out << '(';
  }
  return out << ')';
}

std::ostream &zhalilov::coutBinOp(std::ostream &out, const BinOperator &binOp)
{
  switch (binOp.getType())
  {
  case BinOperator::Type::Addition:
    return out << '+';
  case BinOperator::Type::Subtraction:
    return out << '-';
  case BinOperator::Type::Multiplication:
    return out << '*';
  case BinOperator::Type::Division:
    return out << '/';
  case BinOperator::Type::Mod:
    return out << '%';
  default:
    return out;
  }
}

std::ostream &zhalilov::coutVarExpr(std::ostream &out, const VarExpression &varExpr)
{
  out << varExpr.gerVarName();
  std::list< long long > args = varExpr.getArgs();
  if (!args.empty())
  {
    auto it = args.cbegin();
    out << '(' << *it;
    ++it;
    for (; it != args.cend(); ++it)
    {
      out << ", " << *it;
    }
    out << ')';
  }
  return out;
}
