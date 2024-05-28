#include "input_dict.hpp"
#include "delimeters.hpp"
#include <stdexcept>

std::unordered_map< std::string, std::string > namestnikov::inputDict(std::istream & in)
{
  std::string key = "";
  std::string value = "";
  std::unordered_map< std::string, std::string > res;
  using delC = DelimeterChar;
  while (in >> key >> delC{'-'} >> value)
  {
    res.insert(std::make_pair(key, value));
  }
  if (!in.eof())
  {
    throw std::invalid_argument("Wrong file input");
  }
}