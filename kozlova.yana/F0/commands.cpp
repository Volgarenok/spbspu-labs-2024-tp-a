#include "commands.hpp"
#include <vector>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>
#include "dictionary.hpp"

namespace kozlova
{
  struct isName
  {
    bool operator()(const std::pair<std::string, Dictionary>& pair, const std::string& name)
    {
      return pair.second.getName() == name;
    }
  };

  void read(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string name;
    std::string file;
    in >> name >> file;
    std::ifstream input(file);
    auto pred = std::bind(isName(), std::placeholders::_1, name);
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), pred);
    if (iterator != dictionaries.end() || !in || !input)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict_new;
    dict_new.insertWords(input);
    dictionaries.insert(std::pair< std::string, Dictionary >(name, dict_new));
  }
}
