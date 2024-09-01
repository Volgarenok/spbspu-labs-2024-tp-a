#include "freqList.hpp"
#include <iterator>
#include <ostream>
#include <algorithm>

isaychev::FreqList::FreqList(const std::map< Word, size_t > & rhs):
 list_(rhs)
{}

isaychev::FreqList::FreqList(std::map< Word, size_t > && rhs):
 list_(rhs)
{}

size_t & isaychev::FreqList::at(const Word & rhs) noexcept
{
  return const_cast< size_t & >(static_cast< const FreqList & >(*this).at(rhs));
}

const size_t & isaychev::FreqList::at(const Word & rhs) const noexcept
{
  return list_.at(rhs);
}

void isaychev::FreqList::insert(const Word & rhs)
{
  auto result = list_.insert({rhs, 1});
  if (!result.second)
  {
    (*result.first).second += 1;
  }
}

void isaychev::FreqList::add_element(const value_t & rhs)
{
  auto res = list_.insert(rhs);
  if (!res.second)
  {
    (*res.first).second += rhs.second;
  }
}

size_t isaychev::FreqList::size() const noexcept
{
  return list_.size();
}

bool isaychev::FreqList::empty() const noexcept
{
  return list_.empty();
}

const std::map< isaychev::Word, size_t > & isaychev::FreqList::get_map() const noexcept
{
  return list_;
}

std::string isaychev::convert_to_str(const value_t & rhs)
{
  return std::to_string(rhs.second) + " " + rhs.first.content;
}

std::ostream & isaychev::operator<<(std::ostream & out, const FreqList & rhs)
{
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(rhs.get_map().begin(), rhs.get_map().end(), output_iter_t{out, "\n"}, convert_to_str);
  return out;
}
