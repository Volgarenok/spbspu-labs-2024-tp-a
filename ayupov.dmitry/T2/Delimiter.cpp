#include <istream>
#include <string>
#include <cmath>

#include "Delimiter.hpp"

std::istream& ayupov::operator>>(std::istream& in, DelimiterChar&& exp){
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected){
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& ayupov::operator>>(std::istream& in, DblSciI&& dbl){
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissa = 0.0;
  int power = 1;
  in >> MantissaI{ mantissa } >> power;
  if (in)
  {
    dbl.num = mantissa * std::pow(10, power);
  }
  return in;
}
std::istream& ayupov::operator>>(std::istream& in, MantissaI&& mantissa){
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissaNum = 0.0;
  char current = '0';
  bool isCorrect = true;
  in >> current;
  if (std::isdigit(current)){
    mantissaNum += current - '0';
  }
  else{
    isCorrect = false;
  }
  in >> current;
  if (current != '.'){
    isCorrect = false;
  }
  for (int i = 0; i < 2; i++){
    in >> current;
    if (std::isdigit(current)){
      mantissaNum += (current - '0') * std::pow(10, -1 - i);
    }
    else{
      isCorrect = false;
    }
  }
  in >> current;
  if (std::tolower(current) == 'e' && isCorrect){
    mantissa.mantissa = mantissaNum;
  }
  else{
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& ayupov::operator>>(std::istream& in, StringI&& str){
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterChar{'"'}, str.text, '"');
}
