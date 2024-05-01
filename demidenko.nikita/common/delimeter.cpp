#include "delimeter.hpp"
#include <algorithm>
#include <functional>
#include <iterator>

template <>
void demidenko::DelimeterI::parse(std::istream& in)
{
  using namespace std::placeholders;
  // clang-format off
  auto pred = std::bind(
    std::logical_and<>{},
    std::bind(std::equal_to<>{}, _1, _2),
    std::bind(std::not_equal_to<>{}, _2, '\0')
  );
  // clang-format on
  using InputIterator = std::istream_iterator< char >;
  if (*std::mismatch(InputIterator{ in }, InputIterator{}, data, pred).second != '\0')
  {
    in.setstate(std::ios::failbit);
  }
}
