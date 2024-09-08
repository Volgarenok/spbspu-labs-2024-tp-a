#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <cmath>
#include <functional>

#include "postfix.hpp"
#include "token.hpp"
#include "userCommands.hpp"

int main(int argv, char ** argc)
{
  std::ifstream inFile;
  if (argv == 2)
  {
    inFile.open(argc[1]);
    if (inFile.eof())
    {
      std::cout << '\n';
      return 0;
    }
  }
  using unary = std::map < std::string, std::function< double(const double & ) > >;
  unary unaryCommands;
  unaryCommands["sqrt"] = sqrt;
  unaryCommands["sin"] = sin;
  unaryCommands["cos"] = cos;
  unaryCommands["tg"] = tan;
  unaryCommands["ctg"] = [](double a)
    {
      return (1 / tan(a));
    };
  unaryCommands["abs"] = abs;
  unaryCommands["-"] = std::negate< double >();
  using binary = std::map < std::string, std::function< double(const double &, const double & ) > >;
  binary binaryCommands;
  binaryCommands["+"] = std::plus< double >();
  binaryCommands["-"] = std::minus< double >();
  binaryCommands["/"] = std::divides< double >();
  binaryCommands["*"] = std::multiplies< double >();
  binaryCommands["pow"] = pow;
  using user = std::map < std::string, std::function< void(std::string, unary &, binary & ) > >;
  user userCommands;
  //userCommands["import"] = rebdev::importFile;
  //userCommands["export"] = rebdev::exportFile;
  userCommands["add"] = rebdev::add;
  //userCommands["replace"] = rebdev::replaceCommand;
  std::istream & in = (inFile.is_open() ? inFile : std::cin);
  std::stack< double > resStack;
  while (!in.eof())
  {
    std::string inStr;
    std::getline(in, inStr);
    if (inStr.empty())
    {
      continue;
    }
    std::queue< rebdev::token > postFix;
    try
    {
      rebdev::makePostFix(inStr, postFix, unaryCommands, binaryCommands, userCommands);
      if (postFix.empty())
      {
        continue;
      }
      double num = rebdev::postFixToResult(postFix);
      resStack.push(num);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  if (!resStack.empty())
  {
    size_t stackSize = (resStack.size() - 1);
    for (size_t i = 0; i < stackSize; ++i)
    {
      std::cout << resStack.top() << ' ';
      resStack.pop();
    }
    std::cout << resStack.top();
  }
  std::cout << '\n';
  return 0;
}
