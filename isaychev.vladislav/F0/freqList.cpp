#include "freqList.hpp"
#include <vector>
#include <iterator>
#include <ostream>
#include <algorithm>

void isaychev::FreqList::insert(const Word & rhs)
{
  auto result = list.insert({rhs, 1});
  if (!result.second)
  {
    (*result.first).second += 1;
  }
}

void isaychev::FreqList::add_element(const std::pair< Word, size_t > & rhs)
{
  auto res = list.insert(rhs);
  if (!res.second)
  {
    (*res.first).second += rhs.second;
  }
}

std::string isaychev::convert_to_str(const std::pair< Word, size_t > & rhs)
{
  return std::to_string(rhs.second) + " " + rhs.first.content;
}

std::ostream & isaychev::operator<<(std::ostream & out, const FreqList & rhs)
{
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(rhs.list.begin(), rhs.list.end(), output_iter_t{out, "\n"}, convert_to_str);
  return out;
}
