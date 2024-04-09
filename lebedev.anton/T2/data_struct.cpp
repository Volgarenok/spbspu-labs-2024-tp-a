#include "data_struct.hpp"
#include "input_data.hpp"

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
  output << "(:key1 " << data.key1 << "d";
  output << ":key2 " << data.key2;
  output << ":key3 " << data.key3 << ":)";
  return output;
}
