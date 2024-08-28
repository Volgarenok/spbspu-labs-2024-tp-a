#include "freqList.hpp"
#include <iterator>
#include <ostream>
#include <algorithm>

size_t & isaychev::FreqList::at(const Word & rhs) noexcept
{
  return const_cast< size_t & >(static_cast< const FreqList & >(*this).at(rhs));
}

const size_t & isaychev::FreqList::at(const Word & rhs) const noexcept
{
  return list.at(rhs);
}

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

size_t isaychev::FreqList::size() const noexcept
{
  return list.size();
}

bool isaychev::FreqList::empty() const noexcept
{
  return list.empty();
}

const std::map< isaychev::Word, size_t > & isaychev::FreqList::get_map() const noexcept
{
  return list;
}

std::string isaychev::convert_to_str(const std::pair< Word, size_t > & rhs)
{
  return std::to_string(rhs.second) + " " + rhs.first.content;
}

std::ostream & isaychev::operator<<(std::ostream & out, const FreqList & rhs)
{
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(rhs.get_map().begin(), rhs.get_map().end(), output_iter_t{out, "\n"}, convert_to_str);
  return out;
}
