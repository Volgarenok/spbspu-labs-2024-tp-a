#include "utilities.hpp"
#include <iterator>

bool ishmuratov::is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second)
{
  return second.find(pair.first) != second.cend();
}

bool ishmuratov::not_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second)
{
  return second.find(pair.first) == second.cend();
}

void ishmuratov::process_operations(ishmuratov::dict_t & dictionaries, std::istream & input, func_t operation)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  input >> new_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }

  unit_t temp = operation(dictionaries.at(first_name), dictionaries.at(second_name));
  while (input.get() != '\n' && input >> second_name)
  {
    temp = intersect_impl(temp, dictionaries.at(second_name));
  }
  dictionaries.insert(std::make_pair(new_name, temp));
}

ishmuratov::unit_t ishmuratov::intersect_impl(const unit_t & first, const unit_t & second)
{
  unit_t inter_dict;
  auto pred = std::bind(is_inside, std::placeholders::_1, std::cref(second));
  std::copy_if(first.cbegin(), first.cend(), std::inserter(inter_dict, inter_dict.end()), pred);
  return inter_dict;
}

ishmuratov::unit_t ishmuratov::union_impl(const unit_t & first, const unit_t & second)
{
  unit_t union_dict;
  std::copy(first.cbegin(), first.cend(), std::inserter(union_dict, union_dict.end()));
  auto pred = std::bind(not_inside, std::placeholders::_1, std::cref(first));
  std::copy_if(second.cbegin(), second.cend(), std::inserter(union_dict, union_dict.end()), pred);
  return union_dict;
}

std::ostream & ishmuratov::print_pair_transform(const pair_t & pair, std::ostream & output)
{
  output << pair.first << " ";
  if (!pair.second.empty())
  {
    output << *pair.second.begin();
    std::copy(std::next(pair.second.begin()), pair.second.end(), std::ostream_iterator<std::string>(output, " "));
  }
  output << '\n';
  return output;
}

std::ostream & ishmuratov::operator<<(std::ostream & output, const unit_t & dict)
{
  auto out_it = std::ostream_iterator<char>(output);
  auto bound_print = std::bind(print_pair_transform, std::placeholders::_1, std::ref(output));
  std::transform(dict.begin(), dict.end(), out_it, bound_print);
  return output;
}
