#include "data_struct.hpp"
#include <iomanip>
#include "io_data.hpp"
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
  output << "(:key1 " << DoubleLitOut{ data.key1 };
  output << ":key2 " << DoubleSciOut{ data.key2 };
  output << ":key3 \"" << data.key3 << "\":)";
  return output;
}
