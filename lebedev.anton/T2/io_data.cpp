#include "io_data.hpp"
#include <istream>
#include <iomanip>
#include <cmath>
#include "data_struct.hpp"
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
  input >> temp_num >> Delimiter{'d'};
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
std::ostream & lebedev::operator<<(std::ostream & output, const DoubleLitOut && dbl_lit)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  output << dbl_lit.data << "d";
  return output;
}

std::istream & lebedev::operator>>(std::istream & input, DoubleSci && dbl_sci)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  int num_before_point = 0;
  int num_after_point = 0;
  int power = 0;
  input >> num_before_point >> Delimiter{ '.' } >> num_after_point >> Delimiter{ 'e' } >> power;
  if (input)
  {
    dbl_sci.data = (num_before_point + num_after_point * 0.1) * std::pow(10, power);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
std::ostream & lebedev::operator<<(std::ostream & output, const DoubleSciOut && dbl_sci)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  double num = dbl_sci.data;
  int power = 0;
  char sign = 0;
  if (std::abs(num) >= 10.0)
  {
    sign = '+';
    while (std::abs(num) >= 10.0)
    {
      num /= 10;
      ++power;
    }
  }
  else if (std::abs(num) < 1)
  {
    sign = '-';
    while (std::abs(num) < 1)
    {
      num *= 10;
      ++power;
    }
  }
  else
  {
    sign = '+';
  }
  output << num << "e" << sign << power;
  return output;
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
