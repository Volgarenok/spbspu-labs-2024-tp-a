#ifndef VAREXPRESSION_HPP
#define VAREXPRESSION_HPP

#include <string>
#include <list>

namespace zhalilov
{
  class VarExpression
  {
  public:
    VarExpression();
    VarExpression(const std::string &, const std::string &, const std::list< long long > &);
    std::string getModuleName() const;
    std::string gerVarName() const;
    std::list< long long > getArgs() const;

  private:
    std::string moduleName_;
    std::string varName_;
    std::list< long long > args_;
  };
}

#endif
