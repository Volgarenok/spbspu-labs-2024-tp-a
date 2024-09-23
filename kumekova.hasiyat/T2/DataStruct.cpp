#include "DataStruct.hpp"

namespace kumekova {

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
{
  constexpr auto NoPos = std::string::npos;

  std::string line;
  std::getline(stream, line);

  size_t from = line.find(':');
  if (from == NoPos) {
    throw std::runtime_error("Invalid input format");
  }

  for (size_t i = 0; i < KeyCount; ++i) {
    ++from;
    const auto to = line.find(':', from);
    if (to == NoPos || !parse(std::string(line.c_str() + from, to - from), dataStruct)) {
      throw std::runtime_error("Invalid input format");
    }
    from = to;
  }

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct)
{
  for (size_t i = 0; i < KeyCount; ++i) {
    stream << dataStruct[i];
    if (i < KeyCount - 1) {
      stream << ':';
    }
  }
  return stream;
}

} // namespace kumekova
