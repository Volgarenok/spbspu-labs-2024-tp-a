#include "data_struct.hpp"
#include <iomanip>
#include "input_data.hpp"
#include "scope_guard.hpp"

std::istream & inputKey(std::istream & input, lebedev::DataStruct & data)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string temp_key = "";
  input >> temp_key;
  if (temp_key == "key1")
  {
    input >> lebedev::DoubleLit{ data.key1 };
  }
  else if (temp_key == "key2")
  {
    input >> lebedev::DoubleSci{ data.key2 };
  }
  else if (temp_key == "key3")
  {
    input >> lebedev::String{ data.key3 };
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream & outputDblLit(std::ostream & output, double num)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  lebedev::StreamGuard streamGuard(output);
  output << std::fixed << std::setprecision(1);
  output << num << "d";
  return output;
}

std::ostream & outputDblSci(std::ostream & output, double num)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  lebedev::StreamGuard streamGuard(output);
  output << std::fixed << std::setprecision(1);
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

bool lebedev::DataStruct::operator<(const DataStruct & other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else
  {
    if (key2 != other.key2)
    {
      return key2 < other.key2;
    }
    else
    {
      return key3.size() <= other.key3.size();
    }
  }
}

std::istream & lebedev::operator>>(std::istream & input, DataStruct & data)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  DataStruct temp_data;
  input >> Delimiter{ '(' } >> Delimiter{ ':' };
  inputKey(input, temp_data) >> Delimiter{ ':' };
  inputKey(input, temp_data) >> Delimiter{ ':' };
  inputKey(input, temp_data) >> Delimiter{ ':' };
  input >> Delimiter{ ')' };
  if (input)
  {
    data = temp_data;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream & lebedev::operator<<(std::ostream & output, const DataStruct & data)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << "(:key1 ";
  outputDblLit(output, data.key1);
  output << ":key2 ";
  outputDblSci(output, data.key2);
  output << ":key3 \"" << data.key3 << "\":)";
  return output;
}
