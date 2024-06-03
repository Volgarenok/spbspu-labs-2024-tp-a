#include "varExpression.hpp"

zhalilov::VarExpression::VarExpression():
  args_{}
{}

zhalilov::VarExpression::VarExpression(const std::string &module, const std::string &var, const std::list< long long > &args):
  moduleName_{ module },
  varName_{ var },
  args_{ args }
{}

std::string zhalilov::VarExpression::getModuleName() const
{
  return moduleName_;
}

std::string zhalilov::VarExpression::gerVarName() const
{
  return varName_;
}

std::list< long long > zhalilov::VarExpression::getArgs() const
{
  return args_;
}
