#include <iostream>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional>
#include "dictionary.hpp"

std::ostream & ishmuratov::print_pair_transform(const pair_t & pair, std::ostream & output)
{
  output << pair.first << " ";
  if (!pair.second.empty()) {
    output << *pair.second.begin();
    std::copy(std::next(pair.second.begin()), pair.second.end(), std::ostream_iterator<std::string>(output, " "));
  }
  output << '\n';
  return output;
}

std::ostream & ishmuratov::operator<<(std::ostream& output, const Dictionary & dict)
{
  auto out_it = std::ostream_iterator<char>(output);
  auto bound_print = std::bind(print_pair_transform, std::placeholders::_1, std::ref(output));
  std::transform(dict.data.begin(), dict.data.end(), out_it, bound_print);
  return output;
}

std::istream & ishmuratov::operator>>(std::istream& input, Dictionary & dict)
{
  std::string key;
  std::list<std::string> values;
  if (input >> key) {
    std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(values));
    dict.data[key] = values;
  }
  return input;
}
