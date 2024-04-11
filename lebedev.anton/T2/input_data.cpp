#include "input_data.hpp"
#include <istream>
#include <cmath>
#include "scope_guard.hpp"

std::istream & lebedev::operator>>(std::istream & input, Delimiter && delimiter)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char temp_symb = 0;
  input >> temp_symb;
  if (std::tolower(temp_symb) != delimiter.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream & lebedev::operator>>(std::istream & input, DoubleLit && dbl_lit)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  double temp_num = 0.0;
  input >> temp_num >> Delimiter{ 'd' };
  if (input)
  {
    dbl_lit.data = temp_num;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream & lebedev::operator>>(std::istream & input, DoubleSci && dbl_sci)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  double temp_num = 0.0;
  int temp_power = 1;
  input >> temp_num >> Delimiter{ 'e' } >> temp_power;
  if (input)
  {
    dbl_sci.data = temp_num * std::pow(10, temp_power);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream & lebedev::operator>>(std::istream & input, String && str)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string temp_str = "";
  input >> Delimiter{ '\"' };
  std::getline(input, temp_str, '\"');
  if (input)
  {
    str.data = temp_str;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
