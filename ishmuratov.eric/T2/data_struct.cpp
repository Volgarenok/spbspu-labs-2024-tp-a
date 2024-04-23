#include "data_struct.hpp"
#include <iomanip>

#include "delimeter.hpp"
#include "stream_guard.hpp"

bool ishmuratov::DataStruct::operator<(const ishmuratov::DataStruct & other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else if (key2 != other.key2)
  {
    return std::abs(key2) < std::abs(other.key2);
  }
  return key3.size() < other.key3.size();
}

std::istream & ishmuratov::operator>>(std::istream &input, ishmuratov::DataStruct &value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  using del = Delimeter;
  StreamGuard StreamGuard(input);
  input >> del{'('} >> del{':'};
  std::string temp;

  for (size_t i = 0; i < 3; i++)
  {
    std::string def;
    input >> def;
    if (def == "key1")
    {
      input >> DelimeterUll{value.key1};
    }
    else if (def == "key2")
    {
      input >> DelimeterComplex{value.key2};
    }
    else if (def == "key3")
    {
      input >> DelimeterString{value.key3};
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
    input >> del{':'};
  }
  input >> del{')'};
  return input;
}

std::ostream & ishmuratov::operator<<(std::ostream &output, const ishmuratov::DataStruct &value)
{
  std::ostream::sentry guard(output);
  if (!guard)
  {
    return output;
  }
  output << std::fixed << std::setprecision(1);
  output << "(:key1 " << value.key1 << "ull" << ":key2 #c(";
  output << value.key2.real() << " " << value.key2.imag() << "):key3 \"";
  output << value.key3 << "\":)";
  return output;
}
