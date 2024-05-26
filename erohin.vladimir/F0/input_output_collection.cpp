#include "input_output_collection.hpp"
#include <string>
#include <iostream>
#include <iterator>

namespace erohin
{
  std::pair< std::string, size_t > inputPair(std::istream & input);
}

void erohin::inputDictionary(dictionary & dict, std::istream & input)
{
  return;
}

void erohin::outputDictionary(const dictionary & dict, std::ostream & output)
{
  return;
}

void erohin::inputCollection(collection & context, std::istream & input)
{
  return;
}

void erohin::outputCollection(const collection & context, std::ostream & output)
{
  return;
}

std::pair< std::string, size_t > erohin::inputPair(std::istream & input)
{
  std::string word;
  size_t number = 0;
  input >> word >> number;
  return std::make_pair(word, number);
}
