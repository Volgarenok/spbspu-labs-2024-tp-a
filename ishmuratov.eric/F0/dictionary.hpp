#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "input.hpp"

namespace ishmuratov
{
  using pair_t = std::pair< std::string, std::list< std::string> >;
  struct Dictionary
  {
    unit_t data;
  };

  std::ostream & print_pair_transform(const pair_t & pair, std::ostream & output);
  std::ostream & operator<<(std::ostream& output, const Dictionary& dict);
  std::istream & operator>>(std::istream& input, Dictionary& dict);
}

#endif
