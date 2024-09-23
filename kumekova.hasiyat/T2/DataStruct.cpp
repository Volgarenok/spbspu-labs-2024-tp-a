#include <algorithm>
#include <tuple>

#include "DataStruct.hpp"

namespace kumekova
{
namespace
{

constexpr size_t KeyCount = 3;
constexpr size_t KeyLength = 4; // "keyX"
constexpr size_t SpaceLength = 1; // " "
constexpr size_t PrefixLength = 2; // "0x"
constexpr size_t SuffixLength = 3; // "ULL"

bool parse(const std::string& part, DataStruct& dataStruct)
{
  constexpr auto ValueOffset = KeyLength + SpaceLength;

  const auto partLength = part.size();
  if (partLength < ValueOffset) {
    throw std::runtime_error("Invalid input format");
  }

  const std::string keyStr(part.data(), KeyLength);
  const std::string valueStr(part.data() + ValueOffset, partLength - ValueOffset);

  if (keyStr == "key3") {
    dataStruct.key3 = valueStr;
    return true;
  }

  const auto valueLength = valueStr.size();

  if (keyStr == "key2" && valueLength > PrefixLength) {
    if (valueStr[0] == '0' && std::tolower(valueStr[1]) == 'x') {
      dataStruct.key2 = std::strtoull(valueStr.data(), nullptr, 16);
      return true;
    }
  }

  if (keyStr == "key1" && valueLength > SuffixLength) {
    const auto suffix = valueStr.substr(valueLength - SuffixLength);

    if (std::tolower(suffix[0]) == 'u' && std::tolower(suffix[1]) == 'l' && std::tolower(suffix[2]) == 'l') {
      const auto trimmed = valueStr.substr(0, valueLength - SuffixLength);
      dataStruct.key1 = std::strtoull(trimmed.data(), nullptr, 10);
      return true;
    }
  }

  throw std::runtime_error("Invalid input format");
}

void printHex(std::ostream& stream, const KeyType value)
{
  stream
    << std::uppercase << std::hex << std::showbase
    << value
    << std::nouppercase << std::dec << std::noshowbase;
}

} // namespace

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
{
  constexpr auto NoPos = std::string::npos;
  constexpr auto FailBit = std::ios::failbit;

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
  stream << "(:key1 " << dataStruct.key1 << "ULL:key2 ";
  printHex(stream, dataStruct.key2);
  return stream << ":key3 " << dataStruct.key3 << ":)";
}

bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  return
    std::make_tuple(lhs.key1, lhs.key2, lhs.key3.size()) <
    std::make_tuple(rhs.key1, rhs.key2, rhs.key3.size());
}

}
